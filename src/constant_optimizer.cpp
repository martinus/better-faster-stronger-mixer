#include "bitops/mum.h"
#include "bitops/rot.h"
#include "constant_optimizer/EvalBitFlipSAC.h"
#include "constant_optimizer/MarkovChainMonteCarlo.h"
#include "constant_optimizer/generateUniqueLowEntrophyNumbers.h"
#include "constant_optimizer/mutateBitFlipProbability.h"
#include "doctest.h"
#include "sfc64.h"

#include <chrono>

#include <nmmintrin.h> // for CRC
#include <wmmintrin.h> // for AES

template <size_t S>
class ConstantsProvider {
public:
    using Constants = std::array<uint64_t, S>;

    Constants& constants() {
        return mC;
    }

    Constants const& constants() const {
        return mC;
    }

    uint64_t c(size_t idx) const {
        return mC[idx];
    }

private:
    Constants mC;
};

class Mumx_mumx_rrxx_1 : public ConstantsProvider<1> {
public:
    static constexpr char const* name = "Mumx_mumx_rrxx_1";

    uint64_t operator()(uint64_t v) const noexcept {
        auto a = mumx(v, c(0));
        auto b = v ^ rotr(v, 4) ^ rotr(v ^ c(0), 38);
        return mumx(a, b);
    }
};
TYPE_TO_STRING(Mumx_mumx_rrxx_1);

class Crc_mix : public ConstantsProvider<1> {
public:
    static constexpr char const* name = "Crc_mix";

    uint64_t operator()(uint64_t v) const noexcept {
        auto a = _mm_crc32_u64(0, v) * c(0);
        return a ^ rotr(a, 25) ^ rotr(a ^ c(0), 47);
    }
};
TYPE_TO_STRING(Crc_mix);

class Mumx_mumxx_2 : public ConstantsProvider<2> {
public:
    static constexpr char const* name = "Mumx_mumxx_2";

    uint64_t operator()(uint64_t v) const noexcept {
        return mumx(mumx(v, c(0)), mumx(v, c(1)));
    }
};
TYPE_TO_STRING(Mumx_mumxx_2);

class Aes7 : public ConstantsProvider<1> {
public:
    static constexpr char const* name = "Aes7";

    uint64_t operator()(uint64_t v) const noexcept {
        __m128i hash_64 = _mm_set1_epi64x(v);
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));
        hash_64 = _mm_aesenc_si128(hash_64, _mm_set1_epi32(c(0)));

        // reinterpret_cast is technicall undefined behavior. memcpy is save, and should be fully
        // optimized.
        uint64_t result;
        std::memcpy(&result, &hash_64, sizeof(uint64_t));
        return result;
    }
};
TYPE_TO_STRING(Aes7);

TEST_CASE_TEMPLATE("constant_optimizer" * doctest::skip(), Hasher, Mumx_mumx_rrxx_1, Mumx_mumxx_2,
                   Crc_mix, Aes7) {
    Hasher op;

    sfc64 rng;

    //#if 0
    for (auto& f : op.constants()) {
        //f = UINT64_C(0x609630b4c4831dd1);
        f = rng();
    }
    //#endif

    EvalBitFlipSAC evalBitflipSac(15000);

    // higher means less easily accepted
    MarkovChainMonteCarlo<Hasher> mcmc(10000);

    size_t iter = 0;
    while (true) {
        ++iter;
        auto begin = std::chrono::high_resolution_clock::now();
        std::vector<double> costs{evalBitflipSac(op)};
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<double>(end - begin).count();
        switch (mcmc.accept(op, costs)) {
        case Acceptance::rejected:
            break;

        case Acceptance::accepted:
            std::cout << mcmc << " // " << Hasher::name << " (" << elapsed << " sec)" << std::endl;
            break;

        case Acceptance::new_best:
            evalBitflipSac.show(op);
            std::cout << mcmc << " // " << Hasher::name << " (" << elapsed << " sec) NEW BEST"
                      << std::endl;
            break;
        }
        op = mcmc.accepted();
        mutateBitFlipProbability(&op.constants(), &rng);
        // TODO remember the last 100k mutations?
    }
}
