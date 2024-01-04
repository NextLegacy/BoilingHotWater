#pragma once

#include <memory>

#include "BHW/utils/event/EventSystem.hpp"

#include <forward_list>

namespace BHW
{
    template <typename TECS, typename TEventSystem>
    struct ECSSystem : public TEventSystem
    {
        inline ECSSystem() : TEventSystem() { }
    };
}