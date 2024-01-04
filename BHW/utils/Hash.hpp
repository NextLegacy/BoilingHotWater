#pragma once

#include <string_view>

namespace BHW
{
    inline constexpr unsigned long long Hash(const std::string_view& hash)
    {
        unsigned long long result = 0xcbf29ce484222325; // FNV offset basis

        for (char c : hash) {
            result ^= c;
            result *= 0x100000001b3ULL; // FNV prime
        }

        return result;
    }
}