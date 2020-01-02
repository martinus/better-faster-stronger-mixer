#pragma once

#include <wmmintrin.h> // for AES

#include <cstdint>
#include <cstring> // memcpy

// see https://www.jandrewrogers.com/2019/02/12/fast-perfect-hashing/
inline uint64_t aes2(uint64_t key) {
    __m128i hash_64 = _mm_set1_epi64x(key);
    hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(0xDEADBEEF));
    hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(0xDEADBEEF));

    // reinterpret_cast is technicall undefined behavior. memcpy is save, and should be fully
    // optimized.
    uint64_t result;
    std::memcpy(&result, &hash_64, sizeof(uint64_t));
    return result;
}

inline uint64_t aes3(uint64_t key) {
    __m128i hash_64 = _mm_set1_epi64x(key);
    hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(0xDEADBEEF));
    hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(0xDEADBEEF));
    hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(0xDEADBEEF));

    // reinterpret_cast is technicall undefined behavior. memcpy is save, and should be fully
    // optimized.
    uint64_t result;
    std::memcpy(&result, &hash_64, sizeof(uint64_t));
    return result;
}
