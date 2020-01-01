#include "bitops/rot.h"

#include <cstdint>

// Source: http://mostlymangling.blogspot.com/2019/01/better-stronger-mixer-and-test-procedure.html
inline uint64_t ettinger_mixer(uint64_t v) {
    uint64_t z = (v ^ UINT64_C(0xDB4F0B9175AE2165)) * UINT64_C(0x4823A80B2006E21B);
    z ^= rotl(z, 52) ^ rotl(z, 21) ^ UINT64_C(0x9E3779B97F4A7C15);
    z *= UINT64_C(0x81383173);
    return z ^ z >> 28;
}
