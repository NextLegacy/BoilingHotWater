#include "BHW/utils/time.hpp"

#include <chrono>

namespace BHW
{
    uint64_t NanoSeconds()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>
        (
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
}