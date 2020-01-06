#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>

inline uint64_t mumxmumxx2(uint64_t v) {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    return mumx(mumx(v, a), mumx(v, b));
}

inline uint64_t mumxmumxx_work_in_progress(uint64_t v) {
    static constexpr auto a = UINT64_C(0xa0761d6478bd642f);
    static constexpr auto b = UINT64_C(0xe7037ed1a0b428db);

    // 3.25 v ^ rotr(v, 25) ^ rotr(v, 47) ^ b
    // 3.17 v ^ rotr(v, 25) ^ rotr(v ^ b, 47)
    // 3.20 v ^ rotr(v ^ b, 25) ^ rotr(v, 47)
    // 3.25 v ^ b ^ rotr(v, 25) ^ rotr(v, 47)
    return mumx(mumx(v, a), v ^ rotr(v, 25) ^ rotr(v ^ b, 47));
}
