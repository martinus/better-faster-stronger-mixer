#pragma once

#include "doctest.h"

#include "mixer/mumxmumxx1.h"
#include "mixer/mumxmumxx2.h"
#include "mixer/murmurhash3_fmix64.h"
#include "mixer/wyhash3_mix.h"

#include <tuple>

// creates a class around the given mixer, and provides a name for doctest.
#define MAKE_MIXER_CLASS(mixer)                    \
    class c_##mixer {                              \
    public:                                        \
        uint64_t operator()(uint64_t x) noexcept { \
            return mixer(x);                       \
        }                                          \
        static char const* name() {                \
            return #mixer;                         \
        }                                          \
    };                                             \
    TYPE_TO_STRING(c_##mixer);

// Create class wrapper around the mixer, make it stringifyable, add it to mixer_id test
// instantiation

MAKE_MIXER_CLASS(murmurhash3_fmix64)
MAKE_MIXER_CLASS(mumxmumxx1)
MAKE_MIXER_CLASS(mumxmumxx2)
MAKE_MIXER_CLASS(wyhash3_mix)

using AllMixers = std::tuple<c_murmurhash3_fmix64, c_mumxmumxx1, c_mumxmumxx2, c_wyhash3_mix>;
