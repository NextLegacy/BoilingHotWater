#pragma once

#include <unordered_map>

#include "BHW/utils/reflection/Type.hpp"

namespace BHW
{
    class TypeInfo;

    namespace __reflection
    {
        template <typename TClass, typename ...TInheritedClasses>
        constexpr const TypeInfo& MakeTypeInfo();
    }

    class TypeInfo
    {
    public:
        const std::string_view Name;
        const uint64_t         Hash;

        const std::unordered_map<uint64_t, const TypeInfo&> InheritedClasses;
              std::unordered_map<uint64_t, const TypeInfo&> DerivedClasses  ;

    private:
        TypeInfo(
            std::string_view                                    name            , 
            uint64_t                                            hash            , 
            const std::unordered_map<uint64_t, const TypeInfo&> inheritedClasses
        ) : Name(name), Hash(hash), InheritedClasses(inheritedClasses), DerivedClasses() 
        {
        }

        template <typename TClass, typename ...TInheritedClasses>
        friend constexpr const TypeInfo& __reflection::MakeTypeInfo<TClass, TInheritedClasses...>();
    };

    namespace __reflection
    {
        template <typename TClass, typename ...TInheritedClasses>
        constexpr const TypeInfo& MakeTypeInfo()
        {
            const TypeInfo& typeInfo = *(new TypeInfo
            (
                TypeName<TClass>(),
                TypeHash<TClass>(), 
                { { TypeHash<TInheritedClasses>(), GetTypeInfo<TypeHash<TInheritedClasses>()>() }... }
            ));

            ((const_cast<TypeInfo*>(&GetTypeInfo<TypeHash<TInheritedClasses>()>())->DerivedClasses.insert({ TypeHash<TClass>(), typeInfo })), ...);

            return typeInfo;
        }
    }
    
    template <uint64_t THash>
    constexpr auto Cast(void* ptr);

    template <uint64_t THash>
    inline constexpr const TypeInfo& GetTypeInfo();

    template <typename TClass> 
    inline constexpr bool IsRegistered() { return false; }

    template <typename TClass>
    inline constexpr const TypeInfo& GetTypeInfo()
    {
        static_assert(IsRegistered<TClass>(), "Type is not registered");
    
        return GetTypeInfo<TypeHash<TClass>()>();
    }

/*
    template <typename TType>
    inline constexpr auto Cast(void* ptr)
    {
        return Cast<TypeHash<TType>()>(ptr);
    }
*/
}