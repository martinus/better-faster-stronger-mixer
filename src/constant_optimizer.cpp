#include "bitops/mum.h"
#include "bitops/rot.h"
#include "constant_optimizer/EvalBitFlipSAC.h"
#include "constant_optimizer/MarkovChainMonteCarlo.h"
#include "constant_optimizer/generateUniqueLowEntrophyNumbers.h"
#include "constant_optimizer/mutateBitFlipProbability.h"
#include "doctest.h"
#include "sfc64.h"

#include <chrono>

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

class Mumx_mumx_rrxx_1 : public ConstantsProvider<3> {
public:
    static constexpr char const* name = "Mumx_mumx_rrxx_1";

    uint64_t operator()(uint64_t v) const noexcept {
        return mumx(mumx(v, c(0)), v ^ rotr(v, c(1) & 63) ^ rotr(v ^ c(0), c(2) & 63));
    }
};

TEST_CASE_TEMPLATE("constant_optimizer" * doctest::skip(), Hasher, Mumx_mumx_rrxx_1) {
    Hasher op;

    sfc64 rng;
    Mumx_mumx_rrxx_1::Constants constants;

    //#if 0
    for (auto& f : constants) {
        f = rng();
    }
    //#endif

    EvalBitFlipSAC evalBitflipSac(13);
    MarkovChainMonteCarlo<Hasher> mcmc(1000);

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
    }
}
