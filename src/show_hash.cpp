#include "AllMixersWithClasses.h"
#include "doctest.h"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>

template <typename T>
std::string to_hex(T x) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << std::right << x;
    return ss.str();
}

template <typename Mixer>
void show(uint64_t n) {
    std::cout << to_hex(n) << " " << to_hex(Mixer{}(n)) << " " << Mixer::name() << std::endl;
}

TEST_CASE_TEMPLATE_DEFINE("show" * doctest::skip(), Mixer, mixer_id) {
    for (auto x :
         {UINT64_C(0x0000000000000000), UINT64_C(0x0000000000000001), UINT64_C(0x0000000000000003),
          UINT64_C(0x0000000000000007), UINT64_C(0x0101010101010101), UINT64_C(0x0123456789abcdef),
          UINT64_C(0x084c2a6e195d3b7f), UINT64_C(0x1000000000000001), UINT64_C(0x1111111111111111),
          UINT64_C(0x1fffffffffffffff), UINT64_C(0x3fffffffffffffff), UINT64_C(0x6666666666666666),
          UINT64_C(0x7777777777777777), UINT64_C(0x7f7f7f7f7f7f7f7f), UINT64_C(0x7ffffffffffffff7),
          UINT64_C(0x7fffffffffffffff), UINT64_C(0x8000000000000000), UINT64_C(0x8000000000000008),
          UINT64_C(0x8080808080808080), UINT64_C(0x8888888888888888), UINT64_C(0x9999999999999999),
          UINT64_C(0xc000000000000000), UINT64_C(0xe000000000000000), UINT64_C(0xeeeeeeeeeeeeeeee),
          UINT64_C(0xeffffffffffffffe), UINT64_C(0xf7b3d591e6a2c480), UINT64_C(0xfedcba9876543210),
          UINT64_C(0xfefefefefefefefe), UINT64_C(0xfffffffffffffff8), UINT64_C(0xfffffffffffffffc),
          UINT64_C(0xfffffffffffffffe), UINT64_C(0xffffffffffffffff)}) {
        show<Mixer>(x);
    }
    std::cout << std::endl;
}

TEST_CASE_TEMPLATE_APPLY(mixer_id, AllMixers);