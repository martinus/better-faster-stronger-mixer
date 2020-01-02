#pragma once

#include "bitops/mum.h"

#include <cstdint>

inline size_t robin_hood_hash_int(uint64_t obj) noexcept {
    static constexpr uint64_t k = UINT64_C(0xde5fb9d2630458e9);
    return muma(obj, k);
}
