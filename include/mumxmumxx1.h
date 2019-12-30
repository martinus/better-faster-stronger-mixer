#include "util/mum.h"

#include <cstdint>

inline uint64_t mumxmumxx1(uint64_t v) {
    return mumx(mumx(v, UINT64_C(0x2ca7aea0ebd71d49)), v ^ UINT64_C(0x9e49b5a3555f2294));
}