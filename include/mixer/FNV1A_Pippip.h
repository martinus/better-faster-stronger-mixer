#pragma once

#include <cstdint>

// Dedicated to Pippip, the main character in the 'Das Totenschiff' roman, actually the B.Traven
// himself, his real name was Hermann Albert Otto Maksymilian Feige. CAUTION: Add 8 more bytes to
// the buffer being hashed, usually malloc(...+8) - to prevent out of boundary reads! #include
// <stdint.h> // uint8_t needed #define _PADr_KAZE(x, n) ( ((x) << (n))>>(n) )
//
// source:
// https://software.intel.com/en-us/forums/intel-moderncode-for-parallel-architectures/topic/824947
inline uint64_t FNV1A_Pippip(uint64_t x) {
    return (UINT64_C(14695981039346656037) ^ x) * UINT32_C(591798841);
}
