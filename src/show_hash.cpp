#include "AllMixersWithClasses.h"
#include "bitops/rot.h"
#include "doctest.h"

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
void show(uint64_t n, int r) {
    auto val = rotl(n, r);
    std::cout << to_hex(val) << " " << to_hex(Mixer{}(val)) << " " << Mixer::name() << std::endl;
}

TEST_CASE_TEMPLATE_DEFINE("show" * doctest::skip(), Mixer, mixer_id) {
    for (int r = 0; r < 64; ++r) {
        show<Mixer>(1, r);
        show<Mixer>(2, r);
        show<Mixer>(3, r);
        show<Mixer>(UINT64_C(0xfffffffffffffffe), r);
    }
    std::cout << std::endl;
}

TEST_CASE_TEMPLATE_APPLY(mixer_id, AllMixers);
