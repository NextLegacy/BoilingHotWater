#pragma once

#include <string>
#include <format>

namespace BHW
{
    std::string ToString(const float& f);

    template<typename... TArgs>
    std::string Format(const std::string& format, TArgs&&... messages)
    {
        return std::vformat(format, std::make_format_args(messages...));
    }
}