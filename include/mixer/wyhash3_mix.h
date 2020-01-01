#pragma once

#include "bitops/mum.h"

#include <cstdint>

// Source: https://github.com/wangyi-fudan/wyhash/blob/master/wyhash.h#L39
// should be same when seed=0. Extracted for when len=8
inline uint64_t wyhash3_mix(uint64_t v) noexcept {
    static constexpr auto wyp0 = UINT64_C(0xa0761d6478bd642f);
    static constexpr auto wyp1 = UINT64_C(0xe7037ed1a0b428db);
    static constexpr auto wyp4 = UINT64_C(0x1d8e4e27c47d124f);

    auto a = v & UINT64_C(0x00000000ffffffff);
    auto b = v >> 32U;
    return mumx(mumx(a ^ wyp0, b ^ wyp1), UINT64_C(8) ^ wyp4);
}
