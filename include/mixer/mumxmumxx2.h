#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>

inline uint64_t mumxmumxx2(uint64_t v) {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    return mumx(mumx(v, a), mumx(v, b));
}

// 16
inline uint64_t mumxmumxx3(uint64_t v) {
    v = mumx(v, UINT64_C(0x2ca7aea0ebd71d49));
    v = mumx(v, UINT64_C(0x9e49b5a3555f2295));
    return v;
}
