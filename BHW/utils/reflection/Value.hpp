#pragma once

#include <cstdint>

#include "BHW/utils/reflection/Type.hpp"

#include "BHW/utils/console/Console.hpp"

#include <vector>

#include <BHW/utils/TypeTraits.hpp>

namespace BHW
{
    class Value
    {
    public:
        Value() : m_value(nullptr), m_hash(TypeHash<void>()) { }
        Value(void* value, uint64_t hash) : m_value(value), m_hash(hash) { }

        template <typename T>
        T& Get()
        {
            if constexpr (is_specialization_of_v<std::vector, T>)
            {
                if (Is<std::vector<Value>>())
                {
                    std::vector<Value>& values = *reinterpret_cast<std::vector<Value>*>(m_value);
                    std::vector<typename T::value_type>* result = new std::vector<typename T::value_type>();

                    for (Value& value : values)
                        result->push_back(value.Get<typename T::value_type>());
                    
                    return *result;
                }
            }

            return *reinterpret_cast<T*>(m_value);
        }

        template <typename T>
        void Set(T* value)
        {
            m_value = value;
            m_hash  = TypeHash<T>();
        }

        template <typename T>
        const bool Is() const
        {
            return m_hash == TypeHash<T>();
        }

    public:
        void*    m_value;
        uint64_t m_hash ;
    };
}