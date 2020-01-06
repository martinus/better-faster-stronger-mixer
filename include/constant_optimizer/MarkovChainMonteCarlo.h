#pragma once

#include "Acceptance.h"
#include "geomean.h"
#include "sfc64.h"

#include <vector>

template <typename Individual>
class MarkovChainMonteCarlo {
public:
    MarkovChainMonteCarlo(double beta)
        : mBeta(beta) {}

    Acceptance accept(Individual const& newIndividual, std::vector<double> newCosts) {
        auto acceptedCost = geomean(mAcceptedCost);
        auto newCost = geomean(newCosts);

        ++mTrial;
        auto threshold = std::log(mRng.uniform01()) / mBeta;
        if (newCost <= acceptedCost - threshold) {
            mAccepted = newIndividual;
            mAcceptedCost = newCosts;

            if (newCost < geomean(mBestCost)) {
                mBest = newIndividual;
                mBestCost = newCosts;
                return Acceptance::new_best;
            }

            return Acceptance::accepted;
        }

        return Acceptance::rejected;
    }

    std::vector<double> bestCost() const {
        return mBestCost;
    }

    Individual const& best() const {
        return mBest;
    }

    std::vector<double> acceptedCost() const {
        return mAcceptedCost;
    }

    Individual const& accepted() const {
        return mAccepted;
    }

    size_t trials() const {
        return mTrial;
    }

private:
    sfc64 mRng{};
    size_t mTrial = 0;
    double mBeta = 10.0;

    Individual mBest{};
    std::vector<double> mBestCost{std::numeric_limits<double>::max()};

    Individual mAccepted{};
    std::vector<double> mAcceptedCost{std::numeric_limits<double>::max()};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, MarkovChainMonteCarlo<T> const& mcmc) {
    // printf("%ld: %.5f %.5f: ", mcmc.trials(), mcmc.acceptedCost(), mcmc.bestCost());
    os << mcmc.trials() << ": accepted=(";
    auto prefix = "";
    for (auto c : mcmc.acceptedCost()) {
        os << prefix << c;
        prefix = ", ";
    }
    os << ")=" << geomean(mcmc.acceptedCost()) << ", best=(";
    prefix = "";
    for (auto c : mcmc.bestCost()) {
        os << prefix << c;
        prefix = ", ";
    }
    os << ")=" << geomean(mcmc.bestCost()) << " " << mcmc.best().constants();
    return os;
}

template <size_t S>
std::ostream& operator<<(std::ostream& os, std::array<uint64_t, S> const& factors) {
    auto prefix = "";
    for (auto f : factors) {
        os << prefix << std::hex << "UINT64_C(0x" << f << ")" << std::dec;
        prefix = ", ";
    }
    return os;
}
