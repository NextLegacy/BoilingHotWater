#include "BHW/utils/random/PRNGAlgorithms.hpp"

namespace BHW
{
    namespace PRNGAlgorithms
    {
        constexpr uint64_t Splitmix64(uint64_t &state)
        {
            state += 0x9E3779B97F4A7C15UL;

            uint64_t random = state;

            random = (random ^ (random >> 30)) * 0xBF58476D1CE4E5B9UL;
            random = (random ^ (random >> 27)) * 0x94D049BB133111EBUL;

            return random ^ (random >> 31);
        }

        constexpr uint64_t Xoshiro256ss(uint64_t (&state)[4])
        {
            /*
            uint64_t* s = state;
            uint64_t const result = s[0] + s[3];

            uint64_t const t = s[1] << 17;

            s[2] ^= s[0];
            s[3] ^= s[1];
            s[1] ^= s[2];
            s[0] ^= s[3];

            s[2] ^= t;

            s[3] = (s[3] << 45) | (s[3] >> (64 - 45)); // rotl(s[3], 45);
            */

            uint64_t const result = state[0] + state[3];

            uint64_t const t = state[1] << 17;

            state[2] ^= state[0];
            state[3] ^= state[1];
            state[1] ^= state[2];
            state[0] ^= state[3];

            state[2] ^= t;

            state[3] = (state[3] << 45) | (state[3] >> (64 - 45)); // rotl(state[3], 45);

            return result;
        }
    }
}
