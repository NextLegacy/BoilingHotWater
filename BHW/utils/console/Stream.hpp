#pragma once

#include <string>

#include "BHW/utils/String.hpp"

#include "BHW/utils/event/HybridEventSystem.hpp"

namespace BHW
{
    class OutputEvent
    {
    public:
        virtual ~OutputEvent() = default;

        virtual void OnWrite    (const std::string& message) = 0;
        virtual void OnWriteLine(const std::string& message) = 0;
    };

    template <typename ...TEventSubscribers>
    class OutputStream : public HybridEventSystem<OutputEvent, TEventSubscribers...>
    {
    public:
        inline void Write    (const std::string& message) { typename HybridEventSystem<OutputEvent, TEventSubscribers...>::ForEachEventSystem(&OutputEvent::OnWrite    , message); }
        inline void WriteLine(const std::string& message) { typename HybridEventSystem<OutputEvent, TEventSubscribers...>::ForEachEventSystem(&OutputEvent::OnWriteLine, message); }

        template<typename... TArgs>
        void WriteFormatted(const std::string& format, TArgs&&... messages)
        {
            Write(BHW::Format(format, std::forward<TArgs>(messages)...));
        }

        template<typename... TArgs>
        void WriteLineFormatted(const std::string& format, TArgs&&... messages)
        {
            WriteLine(BHW::Format(format, std::forward<TArgs>(messages)...));
        }
    };

    class InputEvent
    {
    public:
        virtual ~InputEvent() = default;

        virtual void OnRead    (std::string& message) = 0;
        virtual void OnReadLine(std::string& message) = 0;
    };

    template <typename ...TEventSubscribers>
    class InputStream : public HybridEventSystem<InputEvent, TEventSubscribers...>
    {
    public:
        virtual ~InputStream() = default;

        std::string Read    () { std::string message; typename HybridEventSystem<InputEvent, TEventSubscribers...>::ForEachEventSystem(&InputEvent::OnRead    , message); return message; }
        std::string ReadLine() { std::string message; typename HybridEventSystem<InputEvent, TEventSubscribers...>::ForEachEventSystem(&InputEvent::OnReadLine, message); return message; }
    };
}