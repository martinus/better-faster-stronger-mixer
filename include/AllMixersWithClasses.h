#pragma once

#include "doctest.h"

#include "mixer/ettinger_mixer.h"
#include "mixer/lemire_stronglyuniversal.h"
#include "mixer/mumxmumxx1.h"
#include "mixer/mumxmumxx2.h"
#include "mixer/murmurhash3_fmix64.h"
#include "mixer/rrmxmx.h"
#include "mixer/rrxmrrxmsx_0.h"
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

MAKE_MIXER_CLASS(ettinger_mixer)
MAKE_MIXER_CLASS(lemire_stronglyuniversal)
MAKE_MIXER_CLASS(mumxmumxx1)
MAKE_MIXER_CLASS(mumxmumxx2)
MAKE_MIXER_CLASS(murmurhash3_fmix64)
MAKE_MIXER_CLASS(rrmxmx)
MAKE_MIXER_CLASS(rrxmrrxmsx_0)
MAKE_MIXER_CLASS(wyhash3_mix)

using AllMixers =
    std::tuple<c_ettinger_mixer, c_lemire_stronglyuniversal, c_mumxmumxx1, c_mumxmumxx2,
               c_murmurhash3_fmix64, c_rrmxmx, c_rrxmrrxmsx_0, c_wyhash3_mix>;
