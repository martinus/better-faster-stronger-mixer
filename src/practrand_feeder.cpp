#include "doctest.h"

#include "AllMixersWithClasses.h"
#include "BufferedWriter.h"
#include "bitops/bitreverse.h"
#include "bitops/rot.h"

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

TEST_CASE_TEMPLATE_APPLY(mixer_id, AllMixers);
