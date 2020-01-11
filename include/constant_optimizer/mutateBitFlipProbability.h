#pragma once

#include "sfc64.h"

#include <array>

template <size_t S>
void mutateBitFlipProbability(std::array<uint64_t, S>* vals, sfc64* rngPtr) {
    // flip probability 0b111111: (1 - 1/64)^64 = 13% no-flip probability
    auto& rng = *rngPtr;

#if 0
    //if (rng(10) == 0) {
        for (auto& v : *vals) {
            v = rng();
        }

        return;
    //}
#endif

    // flip at least one bit
    (*vals)[rng(vals->size())] ^= UINT64_C(1) << rng(64);

    for (auto& v : *vals) {
        for (size_t b = 0; b < 64; ++b) {
            if (0 == (rng() & 0b111111)) {
                v ^= UINT64_C(1) << b;
            }
        }
    }
}
