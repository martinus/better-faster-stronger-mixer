#pragma once

#include "ColorTable.h"
#include "binomialDistribution.h"
#include "generateUniqueLowEntrophyNumbers.h"
#include "geomean.h"
#include "popcount.h"

#include <array>
#include <cstdint>
#include <iomanip> //setw
#include <vector>

class EvalBitFlipSAC {
    static constexpr int BitsInType = 64;
    using BitFlips = std::array<size_t, BitsInType * BitsInType>;
    using PopCounts = std::array<size_t, BitsInType + 1U>;

public:
    explicit EvalBitFlipSAC(size_t numbers)
        : mBinomialProbs(calculateBinomialDistributionProbabilities(BitsInType, 0.5))
        , mNumbers(numbers) {}

    template <typename Hasher>
    double operator()(Hasher const& hash) const {
        return eval(hash, false);
    }

    template <typename Hasher>
    void show(Hasher const& hash) const {
        eval(hash, true);
    }

private:
    template <typename Hasher>
    double eval(Hasher const& hash, bool printStatus) const {
        double sumChiBitFlips = 0.0;
        double sumChiPopcount = 0.0;

        BitFlips worstCountBitFlips{};
        PopCounts worstPopCounts{};
        double worstChiBitFlips = 0.0;
        double worstChiPopcount = 0.0;

        for (size_t r = 0; r < BitsInType; ++r) {
            for (size_t inverse = 0; inverse < 2; ++inverse) {
                // each rotation gets a separate evaluation
                BitFlips countBitFlips{};
                PopCounts popCounts{};

                for (size_t n = 0; n < mNumbers; ++n) {
                    auto input = rotr(n, r);
                    if (inverse) {
                        input = ~input;
                    }
                    auto h = hash(input);
                    for (size_t i = 0; i < BitsInType; ++i) {
                        auto flipped = h ^ hash(input ^ (1U << i));
                        ++popCounts[popcount(flipped)];

                        for (size_t j = 0; j < BitsInType; ++j) {
                            // fully branch-less code, without any side effects in the inner loop.
                            // This is pretty important so this is fast. The compiler can convert
                            // this into a vpbroadcastq instruction, which makes this whole program
                            // ~20 times faster.
                            //
                            // I played a bit with the code, and this seems to be fastest
                            countBitFlips[i * BitsInType + j] += (flipped >> j) & UINT64_C(1);
                        }
                    }
                }

                // calculate fitness
                auto cf = chiBitFlips(countBitFlips);
                auto cp = chiPopcount(popCounts, 5.0);

                sumChiBitFlips += cf;
                sumChiPopcount += cp;

                if (printStatus) {
                    if (cf > worstChiBitFlips) {
                        worstChiBitFlips = cf;
                        worstCountBitFlips = countBitFlips;
                    }
                    if (cp > worstChiPopcount) {
                        worstChiPopcount = cp;
                        worstPopCounts = popCounts;
                    }
                }
            }
        }

        if (printStatus) {
            printBitFlipProbabilities(worstCountBitFlips);
            printPopcountProbabilities(worstPopCounts, 5.0);
        }

        // geometric mean
        return geomean({sumChiBitFlips / BitsInType, sumChiPopcount / BitsInType});
    }

    // chi^2 for the bit flips. Ideally, each bit is flipped with probability of 1/2
    double chiBitFlips(BitFlips const& countBitFlips) const {
        double expectedFlipsPerBit = static_cast<double>(mNumbers / 2);
        double chi = 0.0;
        for (auto count : countBitFlips) {
            auto diff = (static_cast<double>(count) - expectedFlipsPerBit) / expectedFlipsPerBit;
            chi += diff * diff;
        }
        return chi / static_cast<double>(countBitFlips.size());
    }

    // chi^2 for the distribution of popcount, the "strict avalanche criteria"
    double chiPopcount(std::array<size_t, BitsInType + 1U> const& popCounts,
                       double minCountThreshold = 5.0) const {
        auto totalPopcount = static_cast<double>(mNumbers * BitsInType);
        double chi = 0.0;
        double chiCount = 0.0;
        for (size_t i = 0; i < popCounts.size(); ++i) {
            if (mBinomialProbs[i] * totalPopcount >= minCountThreshold) {
                auto expected = mBinomialProbs[i] * totalPopcount;
                auto actual = static_cast<double>(popCounts[i]);

                auto diff = actual - expected;
                chi += (diff * diff) / expected;
                ++chiCount;
            }
        }

        return chi / chiCount;
    }

    void printBitFlipProbabilities(BitFlips const& countBitFlips) const {
        printf("BitFlipProbabilities:\n");
        auto prob = static_cast<double>(mNumbers);
        for (size_t i = 0; i < BitsInType; ++i) {
            for (size_t j = 0; j < BitsInType; ++j) {
#if 0                
                printf("%3.0f",
                       100.0 * static_cast<double>(countBitFlips[(i + 1) * BitsInType - j - 1]) /
                           prob);
#endif
                auto prob01 =
                    static_cast<double>(countBitFlips[(i + 1) * BitsInType - j - 1]) / prob;

                auto prob01Color = (prob01 - 0.5) * 20 + 0.5;
                if (prob01Color > 1) {
                    prob01Color = 1;
                } else if (prob01Color < 0) {
                    prob01Color = 0;
                }
                auto color = static_cast<uint8_t>(std::round(255.0 * prob01Color));

                colorTableVic().ansiColors(std::cout, color);
                std::cout << std::setw(3) << static_cast<int>(std::round(100.0 * prob01))
                          << "\x1b[0m";
            }
            printf("\n");
        }
        printf("\n");
    }

    void printPopcountProbabilities(PopCounts const& popCounts, double minCountThreshold) const {
        printf("PopcountProbabilities:\n");
        auto totalPopcount = static_cast<double>(mNumbers * BitsInType);
        for (size_t i = 0; i < popCounts.size(); ++i) {
            auto expected = mBinomialProbs[i] * totalPopcount;
            auto actual = static_cast<double>(popCounts[i]);

            printf("%4ld: %13.1f %13.1f: ", i, expected, actual);
            auto chi = 0.0;
            if (mBinomialProbs[i] * totalPopcount >= minCountThreshold) {
                auto diff = actual - expected;
                chi = (diff * diff) / expected;
                printf("%8.3f\n", chi);
            } else {
                printf("   --\n");
            }
        }
    }

    std::vector<double> mBinomialProbs;
    size_t mNumbers;
};