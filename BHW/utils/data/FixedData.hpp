#pragma once

#include "BHW/utils/data/Data.hpp"

namespace BHW
{
    template <size_t TSize, typename TType>
    struct FixedDataStorage : public DataStorage<std::array<TType, TSize>> 
    {
        inline void Create()
        {
            ASSERT(m_index < TSize, "Index out of bounds");

            m_index++;
        }

        inline void Destroy(size_t index)
        {
            ASSERT(index < TSize, "Index out of bounds");
            ASSERT(index < m_index, "Index out of bounds");

            (*this)[index] = (*this)[--m_index];
        }
    
    private:
        size_t m_index = 0;
    };

    template <size_t TSize, typename ...TDataStorages>
    struct FixedDataStorages : public DataStorages<FixedDataStorage<TSize, TDataStorages>...> 
    { 
        inline void Create()
        {
            (std::get<FixedDataStorage<TSize, TDataStorages>>(*this).Create(), ...);
        }

        inline void Destroy(size_t index)
        {
            (std::get<FixedDataStorage<TSize, TDataStorages>>(*this).Destroy(index), ...);
        }

        inline std::tuple<TDataStorages&...> Get(size_t index)
        {
            ASSERT(index < TSize, "Index out of bounds");

            return std::tuple<TDataStorages&...>(std::get<FixedDataStorage<TSize, TDataStorages>>(*this)[index]...);
        }
    };
}