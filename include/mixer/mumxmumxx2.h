#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>

inline uint64_t mumxmumxx2(uint64_t v) {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    return mumx(mumx(v, a), mumx(v, b));
}

// 19
inline uint64_t mumxmumxx_work_in_progress(uint64_t v) {
    static constexpr auto wyp0 = UINT64_C(0xa0761d6478bd642f);
    //static constexpr auto wyp1 = UINT64_C(0xe7037ed1a0b428db);
    static constexpr auto wyp4 = UINT64_C(0x1d8e4e27c47d124f);

    return mumx(mumx(v, wyp0), wyp4);
}
