#pragma once

#include <cstdint>

// source: https://github.com/Cyan4973/xxHash/blob/dev/xxh3.h
inline uint64_t xxh3_mixer(uint64_t input_64) {
    static constexpr auto PRIME32_1 = UINT32_C(0x9E3779B1);
    static constexpr auto PRIME64_2 = UINT64_C(0xC2B2AE3D27D4EB4F);
    static constexpr auto PRIME64_3 = UINT64_C(0x165667B19E3779F9);

    // XXH3_len_4to8_64b
    // constant extracted from kSecret
    auto const keyed = input_64 ^ UINT64_C(0xb8fe6c3923a44bbe);
    auto const mix64 = 8 + ((keyed ^ (keyed >> 51)) * PRIME32_1);
    auto h64 = (mix64 ^ (mix64 >> 47)) * PRIME64_2;

    // XXH3_avalanche
    h64 ^= h64 >> 37;
    h64 *= PRIME64_3;
    h64 ^= h64 >> 32;
    return h64;
}
