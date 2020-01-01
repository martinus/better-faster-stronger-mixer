#include "bitops/rot.h"

#include <cstdint>

// Source: http://mostlymangling.blogspot.com/2019/01/better-stronger-mixer-and-test-procedure.html
//
// New mixer, "rrxmrrxmsx_0", failing one subtest of RR-64-40-TF2-0.94.
// With a unit counter starting at 0, it has passed 128 TB of
// PractRand 0.94 -tf 2 without anomalies found past 2 TB.
inline uint64_t rrxmrrxmsx_0(uint64_t v) {
    v ^= rotr(v, 25) ^ rotr(v, 50);
    v *= UINT64_C(0xA24BAED4963EE407);
    v ^= rotr(v, 24) ^ rotr(v, 49);
    v *= UINT64_C(0x9FB21C651E98DF25);
    return v ^ v >> 28;
}
