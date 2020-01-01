#include "bitops/mum.h"

#include <cstdint>

inline uint64_t mumxmumxx1(uint64_t v) {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2294);
    return mumx(mumx(v, a), v ^ b);
}