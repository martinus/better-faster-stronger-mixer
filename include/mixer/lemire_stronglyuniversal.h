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
    static constexpr uint64_t a1 = UINT64_C(0x65d200ce55b19ad8);
    static constexpr uint64_t b1 = UINT64_C(0x4f2162926e40c299);
    static constexpr uint64_t c1 = UINT64_C(0x162dd799029970f8);
    static constexpr uint64_t a2 = UINT64_C(0x68b665e6872bd1f4);
    static constexpr uint64_t b2 = UINT64_C(0xb6cfcf9d79b51db2);
    static constexpr uint64_t c2 = UINT64_C(0x7a2b92ae912898c2);

    uint64_t low = static_cast<uint32_t>(x);
    uint64_t high = x >> 32;

    return ((a1 * low + b1 * high + c1) >> 32) |
           ((a2 * low + b2 * high + c2) & UINT64_C(0xFFFFFFFF00000000));
}

// Source: https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
inline uint64_t lemire_stronglyuniversal_32(uint64_t x) noexcept {
    // inspired by lemire's strongly universal hashing
    // https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
    //
    // Instead of shifts, we use rotations so we don't lose any bits.
    //
    // Added a final multiplcation with a constant for more mixing. It is most important that the
    // lower bits are well mixed.
    auto a = x * UINT64_C(0xff51afd7ed558ccd);
    auto b = rotr(x, 32U) * UINT64_C(0xc4ceb9fe1a85ec53);
    auto h = rotr(a + b, 32U) * UINT64_C(0xbf58476d1ce4e5b9);
    return h;
}