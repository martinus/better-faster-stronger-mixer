#pragma once

#include <cstddef> // size_t
#include <cstdint>

// Source: http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
inline uint64_t fnv1a_64(uint64_t val) noexcept {
    auto s = reinterpret_cast<uint8_t const*>(&val);

    auto hash = UINT64_C(14695981039346656037);
    for (size_t i = 0; i < sizeof(val); ++i) {
        hash ^= s[i];
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}
