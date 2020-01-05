#include "bitops/rot.h"

#include <cstdint>

inline uint64_t nasam(uint64_t x) noexcept {
    // rotr(a, r) is a 64-bit rotation of a by r bits.
    x ^= rotr(x, 25) ^ rotr(x, 47);
    x *= 0x9E6C63D0676A9A99UL;
    x ^= x >> 23 ^ x >> 51;
    x *= 0x9E6D62D06F6A9A9BUL;
    x ^= x >> 23 ^ x >> 51;

    return x;
}
