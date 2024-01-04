#include "BHW/utils/random/UUID.hpp"


#include <inttypes.h> // Add this line to include the inttypes.h header

namespace BHW
{
    UUID::UUID()
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            m_bytes[i] = 0;
        }
    }

    UUID::UUID(const UUID& other)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            m_bytes[i] = other.m_bytes[i];
        }
    }

    UUID::UUID(const uint8_t* bytes)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            m_bytes[i] = bytes[i];
        }
    }

    UUID::UUID(uint64_t low, uint64_t high)
    {
        m_low  = low ;
        m_high = high;
    }

    std::string UUID::ToString() const
    {
        static char str[37];
        sprintf(str, "%08" PRIx32 "-%04" PRIx16 "-%04" PRIx16 "-%04" PRIx16 "-%012" PRIx64,
            (uint32_t)(m_high >> 32),
            (uint16_t)((m_high >> 16) & 0xFFFF),
            (uint16_t)(m_high & 0xFFFF),
            (uint16_t)((m_low >> 48) & 0xFFFF),
            (uint64_t)(m_low & 0xFFFFFFFFFFFF)
        );
        return str;
    }

    UUID& UUID::operator=(const UUID& other)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            m_bytes[i] = other.m_bytes[i];
        }

        return *this;
    }
}