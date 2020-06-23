#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>
#include <nmmintrin.h> // for CRC

inline uint64_t crc_mul(uint64_t v) noexcept {
    return _mm_crc32_u64(0, v) * UINT64_C(0xbf58476d1ce4e5b9);
}

// |                1.25 |      798,428,778.17 |    0.0% |            7.00 |            4.00 |  1.749 |           0.00 |    0.0% |      0.00 | `crc_mix`
// |                0.71 |    1,403,479,862.36 |    1.1% |            8.00 |            2.28 |  3.512 |           0.00 |    0.0% |      0.00 | `crc_mix`
inline uint64_t crc_mix(uint64_t v) noexcept {
    return _mm_crc32_u64(0, v) ^ (_mm_crc32_u64(0, rotr(v, 44)) << 32);
    //return _mm_crc32_u64(0, v) ^ (_mm_crc32_u64(1, v) << 32);
}
