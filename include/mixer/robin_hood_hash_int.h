#pragma once

#include "bitops/mum.h"

#include <cstdint>

inline size_t robin_hood_hash_int(uint64_t obj) noexcept {
    static constexpr uint64_t k = UINT64_C(0xde5fb9d2630458e9);
    return muma(obj, k);
}

inline size_t robin_hood_hash_int_4_0_0(uint64_t x) noexcept {
    auto h1 = x * UINT64_C(0xA24BAED4963EE407);
    auto h2 = rotr(x, 32U) * UINT64_C(0x9FB21C651E98DF25);
    auto h = rotr(h1 + h2, 32U);
    return static_cast<size_t>(h);
}