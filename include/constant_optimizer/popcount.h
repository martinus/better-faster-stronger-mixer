#pragma once

#include <bitset>
#include <cstddef>

// Will bin in C++20 https://en.cppreference.com/w/cpp/numeric/popcount
template <typename T>
size_t popcount(T v) noexcept {
    // awesomely, this optimize to the popcnt instruction.
    return std::bitset<8 * sizeof(T)>(v).count();
}
