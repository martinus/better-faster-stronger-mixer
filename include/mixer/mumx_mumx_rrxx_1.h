#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>

inline uint64_t mumx_mumx_rrxx_1(uint64_t v) {
    static constexpr auto a = UINT64_C(0xd14fff8ace476a59);

    // mumx(v,a) is not bijective, it only has ~64% coverage. Using data parallel execution, in the
    // meantime we calculate the rrx (rotate & rotate & xor & xor):
    //
    // v ^ rotr(v, 25) ^ rotr(v ^ b, 47)
    //
    // So we get two differently mixed results, both are the input to another final mumx operation
    // to mix them to together.
    //
    // See http://mostlymangling.blogspot.com/2020/01/nasam-not-another-strange-acronym-mixer.html
    return mumx(mumx(v, a), v ^ rotr(v, 25) ^ rotr(v ^ a, 47));
}
