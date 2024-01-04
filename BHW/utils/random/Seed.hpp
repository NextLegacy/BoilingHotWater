#pragma once

#include <string>

#include "BHW/utils/Time.hpp"

#include "BHW/utils/random/PRNGAlgorithms.hpp"

namespace BHW
{
    class Seed
    {
    public:
        Seed();
        Seed(uint64_t seed);
        Seed(std::string seed);

        operator uint64_t   () const;
        operator std::string() const;

        template <unsigned int N>
        inline void CreateState(uint64_t (&state)[N]) const
        {
            uint64_t seed = m_seed;

            for (unsigned int i = 1; i < N; i++)
            {
                state[i] = PRNGAlgorithms::Splitmix64(seed);
            }
        }

    private:
        uint64_t m_seed;
    };
}