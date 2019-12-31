#include "doctest.h"
#include "nanobench.h"

#include "mixer/mumxmumxx1.h"
#include "mixer/murmurhash3_fmix64.h"

TEST_CASE("benchmark") {
    ankerl::nanobench::Config cfg;
    uint64_t n = 1234;
    cfg.run("murmurhash3_fmix64", [&] { n = murmurhash3_fmix64(n); });
    cfg.run("mumxmumxx1", [&] { n = mumxmumxx1(n); });
    ankerl::nanobench::doNotOptimizeAway(n);
}