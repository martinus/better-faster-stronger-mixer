#pragma once

#include "bitops/mum.h"
#include "bitops/rot.h"

#include <cstdint>

/*
  0,02 │158:┌─→movabs     $0xa0761d6478bd642f,%rdx
 31,06 │    │  mulx       %rbx,%rsi,%rdi
  0,05 │    │  movabs     $0xe7037ed1a0b428db,%rax
  0,01 │    │  rorx       $0x19,%rbx,%rcx
  0,01 │    │  xor        %rbx,%rcx
 10,10 │    │  xor        %rax,%rbx
  0,09 │    │  rorx       $0x2f,%rbx,%rbx
  1,32 │    │  xor        %rcx,%rbx
  0,02 │    │  mov        %rdi,%rcx
 13,98 │    │  mov        %rbx,%rdx
  0,09 │    │  xor        %rsi,%rcx
 26,75 │    │  mulx       %rcx,%rax,%rdx
  0,07 │    │  dec        %r14
       │    │  mov        %rdx,%rbx
 13,61 │    │  xor        %rax,%rbx
       │    │  cmp        $0xffffffffffffffff,%r14
  2,82 │    └──jne        158


  0,02 │158:┌─→movabs     $0xa0761d6478bd642f,%rdx
 29,73 │    │  mulx       %rbx,%rsi,%rdi
  0,10 │    │  rorx       $0x19,%rbx,%rcx
       │    │  xor        %rbx,%rcx
  0,15 │    │  xor        %rdx,%rbx
  9,98 │    │  rorx       $0x2f,%rbx,%rbx
  0,99 │    │  xor        %rcx,%rbx
       │    │  mov        %rdi,%rcx
  0,19 │    │  mov        %rbx,%rdx
  8,92 │    │  xor        %rsi,%rcx
 32,13 │    │  mulx       %rcx,%rax,%rdx
  0,04 │    │  dec        %r14
       │    │  mov        %rdx,%rbx
 14,69 │    │  xor        %rax,%rbx
       │    │  cmp        $0xffffffffffffffff,%r14
  3,06 │    └──jne        158

*/
inline uint64_t mumx_mumx_rrxx_1(uint64_t v) {
    static constexpr auto a = UINT64_C(0xa0761d6478bd642f);

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
