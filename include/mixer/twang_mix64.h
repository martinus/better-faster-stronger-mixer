#pragma once

#include <cstdint>

// Thomas Wang 64 bit mix hash function
// see https://github.com/facebook/folly/blob/master/folly/hash/Hash.h#L66
inline uint64_t twang_mix64(uint64_t key) noexcept {
    key = (~key) + (key << 21);
    key = key ^ (key >> 24);
    key = key + (key << 3) + (key << 8);
    key = key ^ (key >> 14);
    key = key + (key << 2) + (key << 4);
    key = key ^ (key >> 28);
    key = key + (key << 31);
    return key;
}
