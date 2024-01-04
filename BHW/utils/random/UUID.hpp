#pragma once

#include <string>

namespace BHW
{
    class UUID
    {
    public:
        UUID();
        UUID(const UUID& other);
        UUID(const uint8_t* bytes);
        UUID(uint64_t low, uint64_t high);

        inline const uint8_t* GetBytes() const { return m_bytes; }
        inline const uint64_t GetLow  () const { return m_low  ; }
        inline const uint64_t GetHigh () const { return m_high ; }

        std::string ToString() const;

        inline bool operator==(const UUID& other) const { return m_low == other.m_low && m_high == other.m_high; }
        inline bool operator!=(const UUID& other) const { return m_low != other.m_low || m_high != other.m_high; }

        UUID& operator=(const UUID& other);
 
    private:
        union
        {
            struct
            {
                uint64_t m_low;
                uint64_t m_high;
            };
            uint8_t m_bytes[16];
        };
    };
}