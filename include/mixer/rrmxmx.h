#include "bitops/rot.h"

#include <cstdint>

// Source: http://mostlymangling.blogspot.com/2019/01/better-stronger-mixer-and-test-procedure.html
inline uint64_t rrmxmx(uint64_t v) {
    v ^= rotr(v, 49) ^ rotr(v, 24);
    v *= UINT64_C(0x9FB21C651E98DF25);
    v ^= v >> 28;
    v *= UINT64_C(0x9FB21C651E98DF25);
    return v ^ v >> 28;
}
