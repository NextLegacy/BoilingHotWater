#pragma once

#include <chrono>
#include <string>

namespace BHW
{
    const struct LoggedMessage
    {
        const std::chrono::system_clock::time_point timestamp;

        const std::string level;

        const std::string message;
    };
}