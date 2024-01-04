#pragma once

#include "BHW/utils/console/Console.hpp"
#include "BHW/utils/TypeTraits.hpp"

#include <ranges>
#include <algorithm>
#include <iostream>

namespace BHW
{
    template <typename TBaseEvent, typename ...TEventSubscribers>
    struct EventSystem
    {
        //static_assert((std::is_base_of_v<TBaseEvent, TEventSubscribers> && ...), "All event systems must derive from the base event system");

        inline EventSystem() : m_systems(std::make_tuple(TEventSubscribers()...)) { }

        template <typename ...TArgs>
        inline void ForEachEventSystem(void (TBaseEvent::*function)(TArgs...), TArgs&&... args)
        {
            ((std::get<TEventSubscribers>(m_systems).*function)(std::forward<TArgs>(args)...), ...);
        }

    private:
        std::tuple<TEventSubscribers...> m_systems;
    };
}

