#include "BHW/utils/random/Random.hpp"

namespace BHW
{
    Splitmix64::Splitmix64(         ) : Prng(    ) { InitState(); }
    Splitmix64::Splitmix64(Seed seed) : Prng(seed) { InitState(); }

    void Splitmix64::InitState() { m_state = m_seed; }

    uint64_t Splitmix64::operator()() { return PRNGAlgorithms::Splitmix64(m_state); }


    Xoshiro256ss::Xoshiro256ss(         ) : Prng(    ) { InitState(); }
    Xoshiro256ss::Xoshiro256ss(Seed seed) : Prng(seed) { InitState(); }

    void Xoshiro256ss::InitState() { m_seed.CreateState(m_state); }
    
    uint64_t Xoshiro256ss::operator()() { return PRNGAlgorithms::Xoshiro256ss(m_state); }
}
