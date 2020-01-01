// Source: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
// License: Public domain

//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

// Note - The x86 and x64 versions do _not_ produce the same results, as the
// algorithms are optimized for their respective platforms. You can still
// compile and run any of them on any platform, but your performance with the
// non-native version will be less than optimal.

/*

murmurhash3_fmix64 identity:
   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
---+----------------------------------------------------------------
 0 |  17  18  18  17  17  16  16  16  16  16  16  17  15  15  15  14
16 |  14  14  14  14  14  15  15  15  16  15  15  16  16  16  15  15
32 |  16  17  17  17  16  15  14  14  15  15  14  15  15  15  15  15
48 |  14  14  14  14  14  14  15  15  15  16  15  16  17  17  17  17
min: 14, max: 18, avg: 15.4

murmurhash3_fmix64 reverse:
   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
---+----------------------------------------------------------------
 0 |  15  16  17  18  18  18  19  19  18  17  17  17  17  16  17  17
16 |  17  16  14  14  14  14  14  16  17  17  17  17  18  18  17  15
32 |  15  14  14  16  16  17  18  18  18  18  17  17  17  17  17  17
48 |  17  16  15  15  14  14  14  15  16  17  17  17  17  18  18  17
min: 14, max: 19, avg: 16.5

*/

#pragma once

#include <cstdint>

inline uint64_t murmurhash3_fmix64(uint64_t h) {
    h ^= h >> 33U;
    h *= UINT64_C(0xff51afd7ed558ccd);
    h ^= h >> 33U;
    h *= UINT64_C(0xc4ceb9fe1a85ec53);
    h ^= h >> 33U;
    return h;
}
