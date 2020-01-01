#include "doctest.h"

#include "bitops/bitreverse.h"
#include "bitops/rot.h"
#include "mixer/mumxmumxx1.h"
#include "mixer/murmurhash3_fmix64.h"
#include "mixer/wyhash3_mix.h"

#include "BufferedWriter.h"

#include <iostream>

// run with e.g.
// clang-format off
// MIXER_ROTATION=11 MIXER_REVERSE=1 ./mixer --out=log.txt -ns -tc="practrand_feeder<c_murmurhash3_fmix64>" | ../../practrand/RNG_test stdin64 -tf 2 -tlmin 1KB -tlmax 40
// clang-format on
TEST_CASE_TEMPLATE_DEFINE("practrand_feeder" * doctest::skip(), Mixer, mixer_id) {
    auto rotationStr = std::getenv("MIXER_ROTATION");
    REQUIRE(rotationStr != nullptr);
    auto rotation = std::atoi(rotationStr);
    REQUIRE(rotation >= 0);
    REQUIRE(rotation <= 64);

    auto isBitreverseStr = std::getenv("MIXER_REVERSE");
    REQUIRE(isBitreverseStr != nullptr);
    auto isBitreverse = std::atoi(isBitreverseStr);
    REQUIRE(isBitreverse >= 0);
    REQUIRE(isBitreverse <= 1);

    freopen(NULL, "wb", stdout); // Only necessary on Windows, but harmless.
    BufferedWriter bufferedWrite(1024, stdout);

    uint64_t ctr = 0;
    Mixer mixer{};

    if (isBitreverse) {
        while (true) {
            bufferedWrite(mixer(bitreverse(rotr(ctr, rotation))));
            ++ctr;
        }
    } else {
        while (true) {
            bufferedWrite(mixer(rotr(ctr, rotation)));
            ++ctr;
        }
    }
}

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
    TYPE_TO_STRING(c_##mixer);                     \
    TEST_CASE_TEMPLATE_INVOKE(mixer_id, c_##mixer);

// Create class wrapper around the mixer, make it stringifyable, add it to mixer_id test
// instantiation

MAKE_MIXER_CLASS(murmurhash3_fmix64)
MAKE_MIXER_CLASS(mumxmumxx1)
MAKE_MIXER_CLASS(wyhash3_mix)
