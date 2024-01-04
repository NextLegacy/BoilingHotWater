#include "BHW/utils/random/Seed.hpp"

namespace BHW
{

    Seed::Seed(uint64_t    seed) : m_seed(seed)                          { }
    Seed::Seed(                ) : Seed(NanoSeconds())                   { }
    Seed::Seed(std::string seed) : Seed(std::hash<std::string>{ }(seed)) { }

    Seed::operator uint64_t   () const { return m_seed                ; }
    Seed::operator std::string() const { return std::to_string(m_seed); }
}