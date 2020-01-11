#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>
#include <nmmintrin.h> // for CRC

inline uint64_t crc_mul(uint64_t v) noexcept {
    return v ^ _mm_crc32_u64(0, v) * UINT64_C(0xbf58476d1ce4e5b9);
}

inline uint64_t crc_mix(uint64_t v) noexcept {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    return mumx(mumx(v, a), b);
}
