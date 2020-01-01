#pragma once

#include <cstdint>

/*

lemire_stronglyuniversal identity:
   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
---+----------------------------------------------------------------
 0 |  12  13  12  12  13  13  10  10  13  12  12  12  10  13  12  12
16 |  13  12  12  12  12  13  12  12  12  12  12  13  12  12  12  12
32 |  12  12  12  12  12  12  12  12  12  12  12  12  13  12  10  12
48 |  12  12  12  12  12  12  12  12  10  12  12  12  12  12  12  13
min: 10, max: 13, avg: 12.0

lemire_stronglyuniversal reverse:
   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
---+----------------------------------------------------------------
 0 |  13  13  13  13  13  13  13  13  12  13  13  12  12  12  13  12
16 |  12  12  12  12  13  13  13  13  12  12  13  14  13  13  14  12
32 |  12  12  13  13  12  12  12  13  13  13  13  13  13  13  13  13
48 |  12  12  13  13  13  13  10  13  13  13  13  13  14  14  13  13
min: 10, max: 14, avg: 12.7
*/

// Source: https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
inline uint64_t lemire_stronglyuniversal(uint64_t x) noexcept {
    auto lo = x & UINT64_C(0x00000000ffffffff);
    auto hi = x >> 32;

    auto r1 = (UINT64_C(0x8532c5125ef9bbee) * lo + UINT64_C(0x61af3eb1d51b4e89) * hi +
               UINT64_C(0xf8eea90faec9c802)) >>
              32;
    auto r2 = (UINT64_C(0x74d28e483bf43464) * lo + UINT64_C(0x8f78acfe4dc2982c) * hi +
               UINT64_C(0x11ae6912bca65735)) >>
              32;
    return (r1 << 32) | r2;
}