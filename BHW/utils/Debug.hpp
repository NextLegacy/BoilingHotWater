#pragma once

#include <string>
#include "BHW/utils/console/Console.hpp"

namespace BHW
{
    template<typename... TArgs>
    void Debug(const std::string& format, TArgs&&... messages)
    {
        Console::WriteLine(BHW::Format(format, std::forward<TArgs>(messages)...));
    }

    template<typename... TArgs>
    void Assert(bool condition, const std::string& format, TArgs&&... messages)
    {
        if (condition) return;

        BHW::Debug(format, std::forward<TArgs>(messages)...);
    }
}

#define BHW_DEBUG(format, ...) BHW::Debug("[DEBUG] [{}:{}]: " format, __FILE__, __LINE__, __VA_ARGS__)
#define BHW_INFO(format, ...) BHW::Debug("[INFO ] [{}:{}]: " format, __FILE__, __LINE__, __VA_ARGS__)
#define BHW_WARN(format, ...) BHW::Debug("[WARN ] [{}:{}]: " format, __FILE__, __LINE__, __VA_ARGS__)
#define BHW_ERROR(format, ...) BHW::Debug("[ERROR] [{}:{}]: " format, __FILE__, __LINE__, __VA_ARGS__)

#define BHW_ASSERT(condition, origin, format, ...) BHW::Assert(condition, "[ASSERT] [{}:{}]: " format, __FILE__, __LINE__, __VA_ARGS__)