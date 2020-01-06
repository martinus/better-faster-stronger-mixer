#pragma once

#include "robin_hood.h"

#include <vector>

inline std::vector<uint64_t> generateUniqueLowEntrophyNumbers(size_t bits) {
    auto constexpr BitsInType = 64;

    robin_hood::unordered_flat_map<uint64_t, char> set;

    std::vector<uint64_t> vec;

    auto iters = 1U << bits;
    for (uint64_t i = 0; i < iters; ++i) {
        for (size_t b = bits - 1; b < BitsInType; ++b) {
            auto val = i ^ (1U << b);
            for (size_t r = 0; r < BitsInType; ++r) {
                auto n = rotr(val, r);
                if (set.emplace(n, '\0').second) {
                    vec.push_back(n);
                }
                n = ~n;
                if (set.emplace(n, '\0').second) {
                    vec.push_back(n);
                }
            }
        }
    }

    return vec;
}
