#pragma once

#include "BHW/utils/Hash.hpp"

#include "BHW/utils/Debug.hpp"

#ifdef __clang__
    #define __FUNCTION_SIGNATURE__ __PRETTY_FUNCTION__
#elif defined(__GNUC__)
    #define __FUNCTION_SIGNATURE__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define __FUNCTION_SIGNATURE__ __FUNCSIG__
#else
    #error "Unsupported compiler"
#endif


namespace BHW
{
    namespace 
    {
        template <typename T>        constexpr std::string_view TypeName();
        template <          > inline constexpr std::string_view TypeName<void>() { return "void"; }

        template <typename T> inline constexpr std::string_view WrappedTypeName() { return __FUNCTION_SIGNATURE__; }
        
        inline constexpr std::size_t WrappedTypeNamePrefixLength()
        {
            return WrappedTypeName<void>().find(TypeName<void>());
        }
        
        inline constexpr size_t WrappedTypeNameSuffixLength()
        {
            return WrappedTypeName<void>().length() - WrappedTypeNamePrefixLength() - TypeName<void>().length();
        }
    
    	template <typename T>
        inline constexpr std::string_view TypeName()
        {
            constexpr auto wrapped_name     = WrappedTypeName<T>();
            constexpr auto prefix_length    = WrappedTypeNamePrefixLength();
            constexpr auto suffix_length    = WrappedTypeNameSuffixLength();
            constexpr auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;

            return wrapped_name.substr(prefix_length, type_name_length);
        }
    }

    struct Type
    {
        const std::string_view Name;
        const uint64_t         Hash;

    private:
        inline constexpr Type(const std::string_view& name) : Name(name), Hash(BHW::Hash(name)) { }

        friend constexpr Type TypeOf(const std::string_view name);

        inline static constexpr Type Create(const std::string_view& name)
        {
            return Type(name);
        }
    };

    template <uint64_t Hash>
    inline constexpr auto Cast(void* ptr)
    {   
        BHW_DEBUG("Type with hash {} is not registered", Hash);
    }

    inline constexpr Type TypeOf(const std::string_view name)
    {
        return Type::Create(name);
    }
    
    template <typename T>
    inline constexpr Type TypeOf()
    {
        return TypeOf(TypeName<T>());
    }

    template <typename T>
    inline constexpr uint64_t TypeHash()
    {
        return Hash(TypeName<T>());
    }
}