#pragma once

#include "umul128.h"

// 128bit multiply a and b, xor high and low result
inline uint64_t mumx(uint64_t a, uint64_t b) {
    uint64_t h;
    uint64_t l = umul128(a, b, &h);
    return h ^ l;
}

// 128bit multiply a and b, add high and low result
inline uint64_t muma(uint64_t a, uint64_t b) {
    uint64_t h;
    uint64_t l = umul128(a, b, &h);
    return h + l;
}
