#pragma once

#include "bitops/rot.h"

#include <cstdint>

// Source: http://mostlymangling.blogspot.com/2019/01/better-stronger-mixer-and-test-procedure.html
inline uint64_t ettinger_mixer1(uint64_t z) {
    z = (z ^ UINT64_C(0xDB4F0B9175AE2165)) * UINT64_C(0x4823A80B2006E21B);
    z ^= rotl(z, 52) ^ rotl(z, 21) ^ UINT64_C(0x9E3779B97F4A7C15);
    z *= UINT64_C(0x81383173);
    return z ^ z >> 28;
}

// Source: https://github.com/tommyettinger/sarong/blob/master/src/main/java/sarong/PelicanRNG.java
inline uint64_t ettinger_mixer2(uint64_t z) {
    z ^= ((z << 41) | (z >> 23)) ^ ((z << 17) | (z >> 47)) ^ UINT64_C(0xD1B54A32D192ED03);
    z *= UINT64_C(0xAEF17502108EF2D9);
    z ^= (z >> 43) ^ (z >> 31) ^ (z >> 23);
    z *= UINT64_C(0xDB4F0B9175AE2165);
    return z ^ (z >> 28);
}
