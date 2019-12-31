#pragma once

#include <array>
#include <cstdint>

struct BitReverseTable {
public:
    constexpr BitReverseTable()
        : mTab{} {
        for (int i = 0; i < 256; ++i) {
            mTab[i] = calcReverse(i);
        }
    }

    constexpr uint8_t operator[](int idx) const {
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

template <typename T>
T bitreverse(T x) {
    static constexpr BitReverseTable bitReverseTable;
    T r = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        r <<= 8;
        r |= bitReverseTable[x & 0xff];
        x >>= 8;
    }
    return r;
}
