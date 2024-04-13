#pragma once

#include "BHW/utils/console/Stream.hpp"

namespace BHW
{
    template <typename ...TOutputStreamEvents> class OutputStreamEvents { public: using OutputStream = OutputStream<TOutputStreamEvents...>; };
    template <typename ...TInputStreamEvents > class InputStreamEvents  { public: using InputStream  = InputStream <TInputStreamEvents... >; };

    template <typename OutputStreamEvents, typename InputStreamEvents>
    class NewConsole : public OutputStreamEvents::OutputStream, public InputStreamEvents::InputStream
    {
    public:
        NewConsole() = default;
    };

    class StdOut : public OutputEvent
    {
    public:
        void OnWrite    (const std::string& message) override { std::cout << message             ; }
        void OnWriteLine(const std::string& message) override { std::cout << message << std::endl; }
    };

    class StdIn : public InputEvent
    {
    public:
        void OnRead    (std::string& message) override { std::cin >> message            ; }
        void OnReadLine(std::string& message) override { std::getline(std::cin, message); }
    };

    extern NewConsole<OutputStreamEvents<StdOut>, InputStreamEvents<StdIn>> StdConsole;
}