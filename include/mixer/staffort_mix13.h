#pragma once

#include <cstdint>

// better constants for murmurhash3_fmxi64
// see http://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
inline uint64_t staffort_mix13(uint64_t h) {
    h ^= h >> 30U;
    h *= UINT64_C(0xbf58476d1ce4e5b9);
    h ^= h >> 27U;
    h *= UINT64_C(0x94d049bb133111eb);
    h ^= h >> 31U;
    return h;
}
