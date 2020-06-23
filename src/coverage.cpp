#include "AllMixersWithClasses.h"
#include "bitops/rot.h"
#include "doctest.h"
#include "fmt/to_hex.h"
#include "robin_hood.h"
#include "sfc64.h"

#include <algorithm>
#include <bitset>
#include <iostream>

#include <nmmintrin.h>

uint16_t mumx16(uint16_t a, uint16_t b) {
    auto m = static_cast<uint32_t>(a) * static_cast<uint32_t>(b);
    m ^= m >> 16;
    return static_cast<uint16_t>(m);
}

uint16_t muma16(uint16_t a, uint16_t b) {
    auto m = static_cast<uint32_t>(a) * static_cast<uint32_t>(b);
    m += m >> 16;
    return static_cast<uint16_t>(m);
}

// 63.2199% coverage
uint32_t mumx32(uint32_t a, uint32_t b) {
    auto m = static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    m ^= m >> 32;
    return static_cast<uint32_t>(m);
}

// 98.8868% coverage with prime 325117817
// 96.9752% prime 1766600701
// 76.0819% prime 4178408657
// 89.0185% coverage with UINT32_C(0x9E3779B1)
uint32_t muma32(uint32_t a, uint32_t b) {
    auto m = static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    return static_cast<uint32_t>(m) + static_cast<uint32_t>(m >> 32);
}

// 63,21% coverage
inline uint32_t mumxmumxx2_32(uint32_t v, uint32_t a, uint32_t b) {
    return mumx32(mumx32(v, a), mumx32(v, b));
}

// 63.21% coverage:
inline uint32_t mumxmumxx3_32(uint32_t v, uint32_t, uint32_t b) {
    v *= 325117817;
    return (v ^ rotr(v, 13) ^ rotr(v ^ b, 23));
}

//////////////

// 48% coverage
inline uint16_t wyhash3_mix16(uint16_t v, uint16_t wyp0, uint16_t wyp1, uint16_t wyp4) {
    uint16_t a = static_cast<uint16_t>(v & 0x00ff);
    uint16_t b = static_cast<uint16_t>(v >> 8U);
    return mumx16(mumx16(a ^ wyp0, b ^ wyp1), UINT16_C(8) ^ wyp4);
}

// 48.63% coverage
inline uint32_t wyhash3_mix32(uint32_t v, uint32_t wyp0, uint32_t wyp1, uint32_t wyp4) {
    uint32_t a = static_cast<uint32_t>(v & 0x0000ffff);
    uint32_t b = static_cast<uint32_t>(v >> 16U);
    return mumx32(mumx32(a ^ wyp0, b ^ wyp1), UINT16_C(8) ^ wyp4);
}

// 39.34% coverage
inline uint32_t wyhash3_rand(uint32_t v, uint32_t wyp0) {
    return mumx32(v ^ wyp0, v);
}

//////

// 100% coverage
inline uint32_t fmix32(uint32_t h) noexcept {
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}

///////

// 74.69% coverage
inline uint32_t lemire_stronglyuniversal32(uint32_t x, uint32_t k1, uint32_t k2, uint32_t k3,
                                           uint32_t k4, uint32_t k5, uint32_t k6) noexcept {
    uint32_t lo = x & UINT32_C(0x0000ffff);
    uint32_t hi = x >> 16;

    uint32_t r1 = (k1 * lo + k2 * hi + k3) >> 16;
    uint32_t r2 = (k4 * lo + k5 * hi + k6) >> 16;
    return (r1 << 16) | r2;
}

// 100% coverage
inline uint32_t crc32(uint32_t v) noexcept {
    return static_cast<uint32_t>(_mm_crc32_u64(0, v));
}

// 100% coverage
inline uint32_t xorshift(uint32_t h) noexcept {
    h ^= h >> 2;
    return h;
}

// 100% coverage
inline uint32_t xorshift2(uint32_t h, uint32_t a) noexcept {
    return a ^ h ^ (h >> 17);
}

inline uint32_t rotrxx(uint32_t x) noexcept {
    return x ^ rotr(x, 25) ^ rotr(x, 13);
}

// 50% coverage
inline uint32_t rotrx(uint32_t x) noexcept {
    return x ^ rotr(x, 25);
}

//
inline uint32_t mumx_mumx_rrxx_1_32(uint32_t v) {
    static constexpr auto a = UINT32_C(1766600701);
    return muma32(v, a); // + (v ^ rotr(v, 4) ^ rotr(v ^ a, 17));
}

class Bitset {
public:
    Bitset(size_t numBits)
        : mData((numBits + 63) / 64) {}

    void set(uint32_t idx) noexcept {
        mData[idx >> 6] |= UINT64_C(1) << (idx & 0x3f);
    }

    bool setAndGet(uint32_t idx) noexcept {
        auto& w64 = mData[idx >> 6];
        auto mask = UINT64_C(1) << (idx & 0x3f);
        bool isSet = (w64 & mask) != 0;
        w64 |= mask;
        return isSet;
    }

    void clear() {
        std::memset(mData.data(), 0, mData.size() * 8);
    }

    void prefetchWrite(uint32_t idx) const noexcept {
        __builtin_prefetch(mData.data() + (idx >> 6), 1, 0);
    }

    size_t count() const noexcept {
        size_t s = 0;
        for (auto d : mData) {
            s += std::bitset<64>(d).count();
        }
        return s;
    }

private:
    std::vector<uint64_t> mData;
};

// real    0m42,976s
// real    0m39,125s prefetch 16

// prefetch idea from
// https://encode.su/threads/3207-ZrHa_update-a-fast-construction-for-iterated-hashing code
// https://gist.github.com/svpv/c305e63110dfc4ab309ad7586ceea277
TEST_CASE("coverage") {
    // can't allocate bitset on the stack => segfault
    static constexpr size_t Size = UINT64_C(1) << 32;
    // auto bits = new std::bitset<Size>();
    auto bits = Bitset(Size);

    sfc64 rng(1234);
#if 0    
    auto k1 = static_cast<uint32_t>(rng() | 1);
    auto k2 = static_cast<uint32_t>(rng() | 1);
    auto k3 = static_cast<uint16_t>(rng() | 1);

    auto k4 = static_cast<uint32_t>(rng() | 1);
    auto k5 = static_cast<uint32_t>(rng() | 1);
    auto k6 = static_cast<uint16_t>(rng() | 1);
#endif

    std::array<uint32_t, 64> tmp;
    tmp.fill(mumx32(0, 0x7849ae79));
    for (size_t i = 0; i < Size; ++i) {
        bits.set(tmp[i % tmp.size()]);
        auto v = mumx32(i, 0x7849ae79);
        bits.prefetchWrite(v);
        tmp[i % tmp.size()] = v;
    }
    for (auto v : tmp) {
        bits.set(v);
    }

    auto ratio = (100.0 * static_cast<double>(bits.count()) / static_cast<double>(Size));
    std::cout << ratio << "% coverage (" << bits.count() << " of " << Size << ")" << std::endl;
}

TEST_CASE("coverage_optimizer") {
    static constexpr size_t Size = UINT64_C(1) << 32;
    sfc64 rng;
    auto bits = Bitset(Size);

    while (true) {
        auto k = static_cast<uint32_t>(rng() | 1);

        std::array<uint32_t, 64> tmp;
        for (size_t i = 0; i < 64; ++i) {
            tmp[i] = mumx32(i, k);
        }

        size_t i = 64;
        for (; i < Size; ++i) {
            if (bits.setAndGet(tmp[i % tmp.size()])) {
                break;
            }
            auto v = mumx32(i, k);
            bits.prefetchWrite(v);
            tmp[i % tmp.size()] = v;
        }

        auto ratio = (100.0 * static_cast<double>(bits.count()) / static_cast<double>(Size));
        std::cout << std::dec << i << " for " << std::hex << "UINT32_C(0x" << k << "). " << std::dec
                  << ratio << "% coverage (" << bits.count() << " of " << Size << ")" << std::endl;

        bits.clear();
    }
}

TEST_CASE("coverage_optimizer16") {
    static constexpr size_t Size = UINT64_C(1) << 16;
    sfc64 rng;
    auto bits = Bitset(Size);

    std::vector<std::pair<size_t, size_t>> data;
    for (size_t k = 0; k < Size; ++k) {
        bits.clear();
        for (size_t i = 0; i < Size; ++i) {
            bits.set(muma16(i, k));
        }

        // auto ratio = (100.0 * static_cast<double>(bits.count()) / static_cast<double>(Size));
        data.emplace_back(bits.count(), k);
    }

    std::sort(data.begin(), data.end());
    for (size_t i = 0; i < data.size(); ++i) {
        // std::cout << data[i].first << " " << std::bitset<16>(data[i].second) << std::endl;
        std::cout << data[i].first << std::endl;
    }
}

uint64_t dummyhash(uint64_t x) {
    uint64_t h;
    umul128(x, UINT64_C(0xa0761d6478bd642f), &h);
    return h;
}

TEST_CASE("find_collisions") {
    auto mask = UINT64_C(0xfffFFFFF);

    uint64_t x = 0;
    uint64_t pre = 0;
    while (true) {
        auto h = robin_hood_hash_int(x);
        //auto h = wyhash3_mix(x);
        if (0 == (h & mask)) {
            std::cout << x << " " << (x - pre) << " -> " << to_hex(h) << std::endl;
            pre = x;
        }
        x += 4056985630;
    }
}

TEST_CASE("collisions") {

    std::vector<size_t> vec(1U << 20);
    auto mask = vec.size() - 1;
    for (size_t i = 0; i < 100000000; ++i) {
        auto x = i << 35;
        //auto h = robin_hood_hash_int(x);
        auto h = dummyhash(x);
        // auto h = mumx_mumx_rrxx_1(x);
        // auto h = nasam(x);
        // auto h = i * UINT64_C(0xa0761d6478bd642f);
        ++vec[h & mask];
    }

    std::sort(vec.begin(), vec.end());
    size_t count = 100;
    for (size_t i = 0; i <= count; ++i) {
        auto idx = (vec.size() - 1) * i / count;
        std::cout << vec[idx] << std::endl;
    }
}

TEST_CASE("coverage64") {
    // can't allocate bitset on the stack => segfault
    robin_hood::unordered_flat_map<uint32_t, uint8_t> map;
    auto bits = Bitset(UINT64_C(1) << 32);

    uint64_t x = 0;
    while (true) {
        // 1598982049 nasam
        // 1598925211 mumx_mumx_rrxx_1
        // 1767169350 robin_hood_hash_int
        for (size_t i = 0; i < 1000000000; ++i) {
            auto h = robin_hood_hash_int(x);
            // auto h = mumx_mumx_rrxx_1(x);
            // auto h = nasam(x);
            bits.set(static_cast<uint32_t>(h));
            bits.set(static_cast<uint32_t>(h >> 32));
            ++x;
        }
        std::cout << bits.count() << std::endl;
        bits.clear();
    }
}