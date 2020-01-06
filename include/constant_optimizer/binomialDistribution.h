#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

// calculates (n over k), see
// https://en.wikipedia.org/wiki/Binomial_coefficient#Computing_the_value_of_binomial_coefficients
inline double binomialCoefficient(size_t n, size_t k) {
    // since B is symmetric, optimize by setting k to the smallest
    k = std::min(k, n - k);

    double prod = 1.0;
    for (size_t i = 1; i <= k; ++i) {
        prod *= static_cast<double>(n + 1U - i) / static_cast<double>(i);
    }
    return prod;
}

inline std::vector<double> calculateBinomialDistributionProbabilities(size_t numberOfTrials,
                                                               double successProbabilityEachTrial) {

    std::vector<double> results;
    for (size_t k = 0; k <= numberOfTrials; ++k) {
        auto r = binomialCoefficient(numberOfTrials, k) *
                 std::pow(successProbabilityEachTrial, static_cast<double>(k)) *
                 std::pow(1 - successProbabilityEachTrial, static_cast<double>(numberOfTrials - k));
        results.push_back(r);
    }

    return results;
}
