#pragma once

#include <type_traits>
#include <string_view>
#include <tuple>

#include "BHW/utils/reflection/TypeInfo.hpp"

namespace BHW
{
    template<typename TClass, typename TType>
    class Member
    {
    public:
        constexpr Member(std::string_view name, TType TClass::* memberPtr) 
            : Name     (name                    ), 
              MemberPtr(memberPtr               ), 
              //Type     (GetTypeInfo<TypeHash<TType >>()),
              //Class    (GetTypeInfo<TypeHash<TClass>>()),
              IsPointer(std::is_pointer_v<TType>) { }

    public:
        const std::string_view Name     ;
              TType TClass::*  MemberPtr;
        //const TypeInfo&        Type     ;
        //const TypeInfo&        Class    ;
        const bool             IsPointer;

    public:
        TType& operator()(TClass& object)
        {
            return object.*MemberPtr;
        }
    };
    
    namespace __reflection
    {
        template<typename TClass, typename ...TMemberTypes>
        constexpr std::tuple<Member<TClass, TMemberTypes>...> MakeMembers(Member<TClass, TMemberTypes>... members)
        {
            return std::make_tuple(members...);
        }

        template<typename TClass, typename TType>
        constexpr Member<TClass, TType> MakeMember(std::string_view name, TType TClass::* memberPtr)
        {
            return Member<TClass, TType>(name, memberPtr);
        }
    }

    template <size_t THash>
    constexpr auto GetMembers()
    {
        return std::make_tuple();
    }

    template <typename TClass>
    constexpr auto GetMembersOfType()
    {
        return GetMembers<TypeHash<TClass>()>();
    }

    template <typename TClass, typename ...TTypes>
    inline constexpr auto MemberPointersToMemberValues(std::tuple<TTypes TClass::*...> tuple, TClass& object)
    {
        std::tuple<TTypes&...> result;

        std::apply([&](auto&&... memberPtrs)
        {
            result = std::make_tuple((object.*memberPtrs)...);
        }, tuple);

        return result;
    }

    template <typename TClass>
    constexpr auto GetMemberValues(TClass& object)
    {
        return MemberPointersToMemberValues(GetMembers<TClass>(), object);
    }
}