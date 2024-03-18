#pragma once

#include <unordered_map>

#include "BHW/utils/reflection/Type.hpp"

namespace BHW
{
    class TypeInfo;

    namespace __reflection
    {
        template <typename TClass, typename ...TInheritedClasses>
        constexpr const TypeInfo& MakeTypeInfo(const std::string_view& sourceLocation);
    }

    class TypeInfo
    {
    public:
        const Type Type;
        
        const std::string_view& SourceLocation;

        const std::unordered_map<uint64_t, const TypeInfo&> InheritedClasses;
              std::unordered_map<uint64_t, const TypeInfo&> DerivedClasses  ;

    private:
        TypeInfo(
            const BHW::Type& type,
            const std::string_view& sourceLocation,
            const std::unordered_map<uint64_t, const TypeInfo&> inheritedClasses
        ) : Type(type), SourceLocation(sourceLocation), InheritedClasses(inheritedClasses), DerivedClasses()
        {
        }

        template <typename TClass, typename ...TInheritedClasses>
        friend constexpr const TypeInfo& __reflection::MakeTypeInfo<TClass, TInheritedClasses...>(const std::string_view& sourceLocation);
    };

    namespace __reflection
    {
        template <typename TClass, typename ...TInheritedClasses>
        constexpr const TypeInfo& MakeTypeInfo(const std::string_view& sourceLocation)
        {
            const TypeInfo& typeInfo = *(new TypeInfo
            (
                TypeOf<TClass>(),
                sourceLocation,
                { { TypeHash<TInheritedClasses>(), GetTypeInfo<TypeHash<TInheritedClasses>()>() }... }
            ));

            ((const_cast<TypeInfo*>(&GetTypeInfo<TypeHash<TInheritedClasses>()>())->DerivedClasses.insert({ TypeHash<TClass>(), typeInfo })), ...);

            return typeInfo;
        }
    }
    
    template <uint64_t THash>
    constexpr auto Cast(void* ptr);

    template <uint64_t THash>
    constexpr const TypeInfo& GetTypeInfo();

    template <uint64_t THash>
    constexpr const std::string_view& GetSourceLocation();

    template <typename TClass> 
    inline constexpr bool IsRegistered() { return false; }

    template <typename TClass>
    inline constexpr const TypeInfo& GetTypeInfo()
    {
        static_assert(IsRegistered<TClass>(), "Type is not registered");
    
        return GetTypeInfo<TypeHash<TClass>()>();
    }

    template <typename TClass>
    inline constexpr const std::string_view& GetSourceLocation()
    {
        return GetSourceLocation<TypeHash<TClass>()>();
    }
}