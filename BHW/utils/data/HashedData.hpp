#pragma once

#include <hash_map>

#include "BHW/utils/data/Data.hpp"

namespace BHW
{
    template <typename TKey, typename TValue>
    struct HashedDataStorage : public DataStorage<std::hash_map<TKey, TValue>> { };
}