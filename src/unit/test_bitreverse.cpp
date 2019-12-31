#include "doctest.h"

#include "bitops/bitreverse.h"

TEST_CASE("bitreverse_uint8_t") {
    REQUIRE(bitreverse<uint8_t>(0b00000000) == 0b00000000);
    REQUIRE(bitreverse<uint8_t>(0b00000001) == 0b10000000);
    REQUIRE(bitreverse<uint8_t>(0b00000010) == 0b01000000);
    REQUIRE(bitreverse<uint8_t>(0b00000100) == 0b00100000);
    REQUIRE(bitreverse<uint8_t>(0b00001000) == 0b00010000);
    REQUIRE(bitreverse<uint8_t>(0b00010000) == 0b00001000);
    REQUIRE(bitreverse<uint8_t>(0b00100000) == 0b00000100);
    REQUIRE(bitreverse<uint8_t>(0b01000000) == 0b00000010);
    REQUIRE(bitreverse<uint8_t>(0b10000000) == 0b00000001);
    REQUIRE(bitreverse<uint8_t>(0b01010101) == 0b10101010);
    REQUIRE(bitreverse<uint8_t>(0b11111111) == 0b11111111);
}

/*
clang-format off
# Generated with some random numbers with this command:
ruby -e 'a=rand(2**64); puts "REQUIRE(bitreverse(UINT64_C(0x#{a.to_s(16)})) == UINT64_C(0x#{a.to_s(2).rjust(64,"0").reverse.to_i(2).to_s(16)}));"'
clang-format on
*/
TEST_CASE("bitreverse_uint64_t") {
    REQUIRE(bitreverse(UINT64_C(0xbe20a09533edf0c)) == UINT64_C(0x30fb7cca905047d0));
    REQUIRE(bitreverse(UINT64_C(0x982e44ce0686cf30)) == UINT64_C(0xcf3616073227419));
    REQUIRE(bitreverse(UINT64_C(0x2ea94cd9c0df1878)) == UINT64_C(0x1e18fb039b329574));
    REQUIRE(bitreverse(UINT64_C(0x203a8767c62c5163)) == UINT64_C(0xc68a3463e6e15c04));
    REQUIRE(bitreverse(UINT64_C(0x91603b1953e20fa2)) == UINT64_C(0x45f047ca98dc0689));
    REQUIRE(bitreverse(UINT64_C(0x6b97dbfd9c131457)) == UINT64_C(0xea28c839bfdbe9d6));
    REQUIRE(bitreverse(UINT64_C(0xcf8bb70646f612ab)) == UINT64_C(0xd5486f6260edd1f3));
    REQUIRE(bitreverse(UINT64_C(0xca24a2bd4744d980)) == UINT64_C(0x19b22e2bd452453));
    REQUIRE(bitreverse(UINT64_C(0x135c4706863d64d8)) == UINT64_C(0x1b26bc6160e23ac8));
    REQUIRE(bitreverse(UINT64_C(0x779f24cd1f0600b2)) == UINT64_C(0x4d0060f8b324f9ee));
    REQUIRE(bitreverse(UINT64_C(0x932638c720da5807)) == UINT64_C(0xe01a5b04e31c64c9));
    REQUIRE(bitreverse(UINT64_C(0x5f68e3e6360cca7e)) == UINT64_C(0x7e53306c67c716fa));
    REQUIRE(bitreverse(UINT64_C(0x74ce31f90f855e6f)) == UINT64_C(0xf67aa1f09f8c732e));
    REQUIRE(bitreverse(UINT64_C(0xf2657c2b6d23b372)) == UINT64_C(0x4ecdc4b6d43ea64f));
    REQUIRE(bitreverse(UINT64_C(0x6aa3bc8f06143f7)) == UINT64_C(0xefc2860f13dc5560));
    REQUIRE(bitreverse(UINT64_C(0x3f532625368d0fbd)) == UINT64_C(0xbdf0b16ca464cafc));
    REQUIRE(bitreverse(UINT64_C(0x3dc79ab195ca991c)) == UINT64_C(0x389953a98d59e3bc));
    REQUIRE(bitreverse(UINT64_C(0xb083e294a9caea55)) == UINT64_C(0xaa5753952947c10d));
    REQUIRE(bitreverse(UINT64_C(0xefd1a5ef6a750992)) == UINT64_C(0x4990ae56f7a58bf7));
    REQUIRE(bitreverse(UINT64_C(0x6fe95d10ab05f9a9)) == UINT64_C(0x959fa0d508ba97f6));
    REQUIRE(bitreverse(UINT64_C(0xc44a004034965708)) == UINT64_C(0x10ea692c02005223));
    REQUIRE(bitreverse(UINT64_C(0x9dcf25f767dd3aaa)) == UINT64_C(0x555cbbe6efa4f3b9));
    REQUIRE(bitreverse(UINT64_C(0x5db84b0ef0d2ffff)) == UINT64_C(0xffff4b0f70d21dba));
    REQUIRE(bitreverse(UINT64_C(0x5863110171dc15aa)) == UINT64_C(0x55a83b8e8088c61a));
    REQUIRE(bitreverse(UINT64_C(0x7be4aa7d52d09212)) == UINT64_C(0x48490b4abe5527de));
    REQUIRE(bitreverse(UINT64_C(0x6ed7331fde473ebb)) == UINT64_C(0xdd7ce27bf8cceb76));
    REQUIRE(bitreverse(UINT64_C(0xe76912918b67ae17)) == UINT64_C(0xe875e6d1894896e7));
    REQUIRE(bitreverse(UINT64_C(0x4a6ad6822f7b6cdb)) == UINT64_C(0xdb36def4416b5652));
    REQUIRE(bitreverse(UINT64_C(0x1464bc476729c4d4)) == UINT64_C(0x2b2394e6e23d2628));
    REQUIRE(bitreverse(UINT64_C(0x1e17370ac8007c30)) == UINT64_C(0xc3e001350ece878));
    REQUIRE(bitreverse(UINT64_C(0xd17b28add427de5a)) == UINT64_C(0x5a7be42bb514de8b));
    REQUIRE(bitreverse(UINT64_C(0x4bc1aa770d381a5e)) == UINT64_C(0x7a581cb0ee5583d2));
    REQUIRE(bitreverse(UINT64_C(0xe767d719daad5ed2)) == UINT64_C(0x4b7ab55b98ebe6e7));
    REQUIRE(bitreverse(UINT64_C(0xc00d443e1384deb4)) == UINT64_C(0x2d7b21c87c22b003));
    REQUIRE(bitreverse(UINT64_C(0xa77c0566fd342cd3)) == UINT64_C(0xcb342cbf66a03ee5));
    REQUIRE(bitreverse(UINT64_C(0xffc2683b81fa32d7)) == UINT64_C(0xeb4c5f81dc1643ff));
    REQUIRE(bitreverse(UINT64_C(0xf8b55cc0b644f951)) == UINT64_C(0x8a9f226d033aad1f));
    REQUIRE(bitreverse(UINT64_C(0x2ed5f9053e594ea1)) == UINT64_C(0x85729a7ca09fab74));
    REQUIRE(bitreverse(UINT64_C(0x50ea4a4fd535cb91)) == UINT64_C(0x89d3acabf252570a));
    REQUIRE(bitreverse(UINT64_C(0x9561b9a976553de8)) == UINT64_C(0x17bcaa6e959d86a9));
    REQUIRE(bitreverse(UINT64_C(0x5c14aaf9a8fda2b)) == UINT64_C(0xd45bf159f55283a0));
}
