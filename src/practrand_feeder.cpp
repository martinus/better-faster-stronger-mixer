#include "doctest.h"

#include "bitops/rot.h"
#include "mixer/mumxmumxx1.h"
#include "mixer/murmurhash3_fmix64.h"

#include "BufferedWriter.h"

#include <iostream>

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

MAKE_MIXER_CLASS(murmurhash3_fmix64)
MAKE_MIXER_CLASS(mumxmumxx1)

// run with --out=/dev/null
TEST_CASE_TEMPLATE("practrand_feeder" * doctest::skip(), Mixer, c_murmurhash3_fmix64,
                   c_mumxmumxx1) {
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
    std::cerr << Mixer::name() << ", rotation=" << rotation << ", bitreverse=" << isBitreverse
              << std::endl;
    while (true) {
        bufferedWrite(mixer(rotr(ctr, rotation)));
        ++ctr;
    }
}
