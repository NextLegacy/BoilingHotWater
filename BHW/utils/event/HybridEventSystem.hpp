#pragma once

#include "BHW/utils/event/EventSystem.hpp"
#include "BHW/utils/event/DynamicEventSystem.hpp"

namespace BHW
{
    template <typename TBaseEvent, typename ...TEventSubscribers>
    struct HybridEventSystem : EventSystem<TBaseEvent, TEventSubscribers...>, DynamicEventSystem<TBaseEvent>
    {
        inline HybridEventSystem() : EventSystem<TBaseEvent, TEventSubscribers...>(), DynamicEventSystem<TBaseEvent>() { }

        template <typename ...TArgs>
        inline void ForEachEventSystem(void (TBaseEvent::*function)(TArgs...), TArgs&&... args)
        {
            EventSystem<TBaseEvent, TEventSubscribers...>::ForEachEventSystem(function, std::forward<TArgs>(args)...);
            DynamicEventSystem<TBaseEvent>::ForEachEventSystem(function, std::forward<TArgs>(args)...);
        }
    };
}