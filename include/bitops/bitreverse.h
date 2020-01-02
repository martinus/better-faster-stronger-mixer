#pragma once

#include <cstdint>

template <typename T>
struct BitReverseTable {
public:
    constexpr BitReverseTable()
        : mTab{} {
        for (int i = 0; i < 256; ++i) {
            mTab[i] = calcReverse(i);
        }
    }

    constexpr T operator[](int idx) const {
        return mTab[idx];
    }

private:
    static constexpr uint8_t calcReverse(uint8_t x) {
        uint8_t r = 0;
        for (int i = 0; i < 8; ++i) {
            r <<= 1;
            r |= x & 1;
            x >>= 1;
        }
        return r;
    }

    uint8_t mTab[256];
};

inline uint8_t bitreverse8(uint8_t x) {
    static constexpr BitReverseTable<uint8_t> t;
    return t[x];
}

inline uint32_t bitreverse32(uint32_t x) {
    static constexpr BitReverseTable<uint32_t> t;

    return ((t[x & 0xff]) << 24) | ((t[(x >> 8) & 0xff]) << 16) | ((t[(x >> 16) & 0xff]) << 8) |
           t[x >> 24];
}

inline uint64_t bitreverse64(uint64_t x) {
    static constexpr BitReverseTable<uint64_t> t;

    return ((t[x & 0xff]) << 56) | ((t[(x >> 8) & 0xff]) << 48) | ((t[(x >> 16) & 0xff]) << 40) |
           ((t[(x >> 24) & 0xff]) << 32) | ((t[(x >> 32) & 0xff]) << 24) |
           ((t[(x >> 40) & 0xff]) << 16) | ((t[(x >> 48) & 0xff]) << 8) | t[x >> 56];
}