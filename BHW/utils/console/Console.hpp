#pragma once

#ifdef _WIN32

    #include <Windows.h>
    
#endif

#include <iostream>

#include "BHW/utils/String.hpp"

namespace BHW
{
    namespace Console
    {
        void Initialize();
        void Shutdown  ();

        void Write    (const std::string& message);
        void WriteLine(const std::string& message);

        template<typename... TArgs>
        void WriteLineFormatted(const std::string& format, TArgs&&... messages)
        {
            WriteLine(BHW::Format(format, std::forward<TArgs>(messages)...));
        }

        void Pause();

        std::string ReadLine();
    }
}