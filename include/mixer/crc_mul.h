#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>
#include <nmmintrin.h> // for CRC

inline uint64_t crc_mul(uint64_t v) noexcept {
    return _mm_crc32_u64(0, v) * UINT64_C(0xbf58476d1ce4e5b9);
}

inline uint64_t crc_mix(uint64_t v) noexcept {
    v = _mm_crc32_u64(0, v) * UINT64_C(0x43ff7ee6d57ee22d);
    return v ^ rotr(v, 25) ^ rotr(v ^ UINT64_C(0x43ff7ee6d57ee22d), 47);
}
