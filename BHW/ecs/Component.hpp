#pragma once

#include <cstdint>

namespace BHW
{
    // is determined at compile time | determines the index of a componentType
    typedef uint64_t ComponentTypeUUID;

    // changes undeterministically at runtime | determines the index of a component
    typedef uint64_t ComponentIndex;

    // combines ComponentTypeUUID and ComponentIndex | (ComponentTypeUUID << 32) | (ComponentIndex)
    typedef uint64_t ComponentUUID;

    template <typename ...TComponents>
    struct ComponentBitMask;
}