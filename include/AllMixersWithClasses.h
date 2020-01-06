#pragma once

#include "doctest.h"

#include "mixer/FNV1A_Pippip.h"
#include "mixer/aes.h"
#include "mixer/crc_mul.h"
#include "mixer/ettinger_mixer.h"
#include "mixer/fnv1a_64.h"
#include "mixer/lemire_stronglyuniversal.h"
#include "mixer/mum3_mixer.h"
#include "mixer/mumx_mumx_rrxx_1.h"
#include "mixer/mumxmumxx1.h"
#include "mixer/mumxmumxx2.h"
#include "mixer/murmurhash3_fmix64.h"
#include "mixer/nasam.h"
#include "mixer/robin_hood_hash_int.h"
#include "mixer/rrmxmx.h"
#include "mixer/rrxmrrxmsx_0.h"
#include "mixer/staffort_mix13.h"
#include "mixer/twang_mix64.h"
#include "mixer/wyhash3_mix.h"
#include "mixer/xxh3_mixer.h"

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

MAKE_MIXER_CLASS(FNV1A_Pippip)
MAKE_MIXER_CLASS(aes2)
MAKE_MIXER_CLASS(aes3)
MAKE_MIXER_CLASS(crc_mix)
MAKE_MIXER_CLASS(crc_mul)
MAKE_MIXER_CLASS(ettinger_pelican)
MAKE_MIXER_CLASS(ettinger_mixer1)
MAKE_MIXER_CLASS(fnv1a_64)
MAKE_MIXER_CLASS(lemire_stronglyuniversal)
MAKE_MIXER_CLASS(mum3_mixer)
MAKE_MIXER_CLASS(mumxmumxx1)
MAKE_MIXER_CLASS(mumxmumxx2)
MAKE_MIXER_CLASS(mumx_mumx_rrxx_1)
MAKE_MIXER_CLASS(murmurhash3_fmix64)
MAKE_MIXER_CLASS(nasam)
MAKE_MIXER_CLASS(robin_hood_hash_int)
MAKE_MIXER_CLASS(rrmxmx)
MAKE_MIXER_CLASS(rrxmrrxmsx_0)
MAKE_MIXER_CLASS(staffort_mix13)
MAKE_MIXER_CLASS(twang_mix64)
MAKE_MIXER_CLASS(wyhash3_mix)
MAKE_MIXER_CLASS(xxh3_mixer)

using AllMixers =
    std::tuple<c_FNV1A_Pippip, c_aes2, c_aes3, c_crc_mix, c_crc_mul, c_ettinger_mixer1,
               c_ettinger_pelican, c_fnv1a_64, c_lemire_stronglyuniversal, c_mum3_mixer,
               c_mumxmumxx1, c_mumxmumxx2, c_mumx_mumx_rrxx_1, c_murmurhash3_fmix64, c_nasam,
               c_robin_hood_hash_int, c_rrmxmx, c_rrxmrrxmsx_0, c_staffort_mix13, c_twang_mix64,
               c_wyhash3_mix, c_xxh3_mixer>;
