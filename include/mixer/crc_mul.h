#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>
#include <nmmintrin.h>

inline uint64_t crc_mul(uint64_t v) noexcept {
    auto a = _mm_crc32_u64(0, v);
    return mumx(a ^ UINT64_C(0xbf58476d1ce4e5b9), a ^ UINT64_C(0x94d049bb133111eb));
}
