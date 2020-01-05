#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "bitops/mum.h"

// read 8 bytes
inline uint64_t mumxmumxx2_read8(uint8_t const* p) noexcept {
    uint64_t v;
    std::memcpy(&v, p, 8);
    return v;
}

// read 4 bytes  (lower bytes of return value)
inline uint64_t mumxmumxx2_read4(uint8_t const* p) noexcept {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}

// reads 1 to 3 bytes.
// * k=1: p[0], p[0], p[0]
// * k=2: p[0], p[1], p[1]
// * k=3: p[0], p[1], p[2]
inline uint64_t mumxmumxx2_read1to3(uint8_t const* p, size_t k) noexcept {
    return (static_cast<uint64_t>(p[0]) << 16U) | (static_cast<uint64_t>(p[k >> 1U]) << 8U) |
           p[k - 1U];
}

inline uint64_t mumxmumxx2_mix(uint64_t v) {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    return mumx(mumx(v, a), mumx(v, b));
}

inline uint64_t mumxmumxx2_hash(void const* key, size_t len, uint64_t seed) noexcept {
    static constexpr auto a = UINT64_C(0x2ca7aea0ebd71d49);
    static constexpr auto b = UINT64_C(0x9e49b5a3555f2295);

    auto p = reinterpret_cast<uint8_t const*>(key);
    if (len < 4) {
        return mumxmumxx2_mix(seed ^ mumxmumxx2_read1to3(p, len));
    }
    if (len <= 8) {
        return mumxmumxx2_mix(seed ^ mumxmumxx2_read4(p) ^ mumxmumxx2_read4(p + len - 4));
    }
    if (len <= 16) {
        auto p1 = seed ^ mumxmumxx2_read8(p);
        auto p2 = mumxmumxx2_read8(p + len - 8);
        return mumx(mumx(p1, a), mumx(p2, b));
    }
    if (len <= 24) {
        auto p1 = seed ^ mumxmumxx2_read8(p);
        auto p2 = mumxmumxx2_read8(p + 8);
        auto p3 = mumxmumxx2_read8(p + len - 8);

        auto h1 = mumx(mumx(p1, a), mumx(p2, b));
        return mumx(mumx(h1, a), mumx(p2, b));
    }
    if (len <= 32) {
        auto p1 = seed ^ mumxmumxx2_read8(p);
        auto p2 = mumxmumxx2_read8(p + 8);
        auto p3 = mumxmumxx2_read8(p + 16);
        auto p4 = mumxmumxx2_read8(p + len - 8);

        auto h1 = mumx(mumx(p1, a), mumx(p2, b));
        auto h2 = mumx(mumx(p3, a), mumx(p4, b));
        return mumx(mumx(h1, a), mumx(h2, b));
    }

    uint64_t see1 = seed, i = len;
    if (i >= 256)
        for (; i >= 256; i -= 256, p += 256) {
            seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 16) ^ seed ^ _wyp2, _wyr8(p + 24) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 32) ^ see1 ^ _wyp1, _wyr8(p + 40) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 48) ^ see1 ^ _wyp3, _wyr8(p + 56) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 64) ^ seed ^ _wyp0, _wyr8(p + 72) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 80) ^ seed ^ _wyp2, _wyr8(p + 88) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 96) ^ see1 ^ _wyp1, _wyr8(p + 104) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 112) ^ see1 ^ _wyp3, _wyr8(p + 120) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 128) ^ seed ^ _wyp0, _wyr8(p + 136) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 144) ^ seed ^ _wyp2, _wyr8(p + 152) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 160) ^ see1 ^ _wyp1, _wyr8(p + 168) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 176) ^ see1 ^ _wyp3, _wyr8(p + 184) ^ see1 ^ _wyp0);
            seed = _wymum(_wyr8(p + 192) ^ seed ^ _wyp0, _wyr8(p + 200) ^ seed ^ _wyp1) ^
                   _wymum(_wyr8(p + 208) ^ seed ^ _wyp2, _wyr8(p + 216) ^ seed ^ _wyp3);
            see1 = _wymum(_wyr8(p + 224) ^ see1 ^ _wyp1, _wyr8(p + 232) ^ see1 ^ _wyp2) ^
                   _wymum(_wyr8(p + 240) ^ see1 ^ _wyp3, _wyr8(p + 248) ^ see1 ^ _wyp0);
        }
    for (; i >= 32; i -= 32, p += 32) {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 = _wymum(_wyr8(p + 16) ^ see1 ^ _wyp2, _wyr8(p + 24) ^ see1 ^ _wyp3);
    }
    if (!i) {
    } else if (i < 4)
        seed = _wymum(_wyr3(p, i) ^ seed ^ _wyp0, seed ^ _wyp1);
    else if (i <= 8)
        seed = _wymum(_wyr4(p) ^ seed ^ _wyp0, _wyr4(p + i - 4) ^ seed ^ _wyp1);
    else if (i <= 16)
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + i - 8) ^ seed ^ _wyp1);
    else if (i <= 24) {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 = _wymum(_wyr8(p + i - 8) ^ see1 ^ _wyp2, see1 ^ _wyp3);
    } else {
        seed = _wymum(_wyr8(p) ^ seed ^ _wyp0, _wyr8(p + 8) ^ seed ^ _wyp1);
        see1 = _wymum(_wyr8(p + 16) ^ see1 ^ _wyp2, _wyr8(p + i - 8) ^ see1 ^ _wyp3);
    }
    return _wymum(seed ^ see1, len ^ _wyp4);
}