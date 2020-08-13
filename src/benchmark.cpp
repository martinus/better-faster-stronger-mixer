#include "AllMixersWithClasses.h"
#include "doctest.h"
#include "nanobench.h"

TEST_CASE_TEMPLATE_DEFINE("benchmark", Mixer, mixer_id) {
    ankerl::nanobench::Bench bench;

    uint64_t n = UINT64_C(0xfedcba9876543210);
    Mixer mixer;
    bench.run(Mixer::name(), [&] {
        //n = mixer(n);
        ankerl::nanobench::doNotOptimizeAway(mixer(n++));
    });
    ankerl::nanobench::doNotOptimizeAway(n);
}
TEST_CASE_TEMPLATE_APPLY(mixer_id, AllMixers);
