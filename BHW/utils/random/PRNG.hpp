#pragma once

#include <string>
#include "BHW/utils/random/Seed.hpp"
#include "BHW/utils/random/UUID.hpp"

namespace BHW
{
    template <typename TState>
    class Prng
    {
    public:
        Prng() : Prng(Seed()) { }
        Prng(Seed seed) : m_state() { SetSeed(seed); }

        inline Seed GetSeed() const { return m_seed; }
        inline void SetSeed(Seed seed) { m_seed = seed; }

        virtual void InitState() { }

        inline int64_t  Int64  () { return (int64_t ) UInt64 (   )                      ; }
        inline int32_t  Int32  () { return (int32_t ) Int64  (   )                      ; }
        inline int16_t  Int16  () { return (int16_t ) Int64  (   )                      ; }
        inline int8_t   Int8   () { return (int8_t  ) Int64  (   )                      ; }
        inline uint64_t UInt64 () { return (uint64_t) (*this)(   )                      ; }
        inline uint32_t UInt32 () { return (uint32_t) UInt64 (   )                      ; }
        inline uint16_t UInt16 () { return (uint16_t) UInt64 (   )                      ; }
        inline uint8_t  UInt8  () { return (uint8_t ) UInt64 (   )                      ; }
        inline float    Float32() { return (float   ) UInt64 (   ) / (float ) UINT64_MAX; }
        inline double   Float64() { return (double  ) UInt64 (   ) / (double) UINT64_MAX; }
        inline bool     Bool   () { return (bool    ) Bool   (0.5)                      ; }

        inline int64_t  Int64 (int64_t  bound) { return (int64_t ) Int64 (     ) % bound; } // TODO: I really don't like modulo
        inline int32_t  Int32 (int32_t  bound) { return (int32_t ) Int64 (bound);         }
        inline int16_t  Int16 (int16_t  bound) { return (int16_t ) Int64 (bound);         }
        inline int8_t   Int8  (int8_t   bound) { return (int8_t  ) Int64 (bound);         }
        inline uint64_t UInt64(uint64_t bound) { return (uint64_t) UInt64(     ) % bound; } // TODO: I really don't like modulo
        inline uint32_t UInt32(uint32_t bound) { return (uint32_t) UInt64(bound);         }
        inline uint16_t UInt16(uint16_t bound) { return (uint16_t) UInt64(bound);         }
        inline uint8_t  UInt8 (uint8_t  bound) { return (uint8_t ) UInt64(bound);         }

        int64_t  Int64  (int64_t  min, int64_t  max) { return Int64 (max - min) + min; }
        int32_t  Int32  (int32_t  min, int32_t  max) { return Int32 (max - min) + min; }
        int16_t  Int16  (int16_t  min, int16_t  max) { return Int16 (max - min) + min; }
        int8_t   Int8   (int8_t   min, int8_t   max) { return Int8  (max - min) + min; }
        uint64_t UInt64 (uint64_t min, uint64_t max) { return UInt64(max - min) + min; }
        uint32_t UInt32 (uint32_t min, uint32_t max) { return UInt32(max - min) + min; }
        uint16_t UInt16 (uint16_t min, uint16_t max) { return UInt16(max - min) + min; }
        uint8_t  UInt8  (uint8_t  min, uint8_t  max) { return UInt8 (max - min) + min; }

        float    Float32(float    min, float    max) { return Float32() * (max - min) + min; }
        double   Float64(double   min, double   max) { return Float64() * (max - min) + min; }

        bool Bool(double probability) { return Float64() < probability; }

        std::string String(unsigned int length, const std::string& charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")    
        {
            std::string result;

            for (unsigned int i = 0; i < length; i++)
            {
                result += charset[UInt64(0, charset.length() - 1)];
            }

            return result;
        }

        UUID UUID()
        {
            return BHW::UUID(UInt64(), UInt64());
        }

        virtual uint64_t operator()() = 0;

    protected:
        Seed   m_seed ;
        TState m_state;
    };
}