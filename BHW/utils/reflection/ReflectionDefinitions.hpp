#pragma once

#include "BHW/utils/reflection/Type.hpp"
#include "BHW/utils/reflection/TypeInfo.hpp"

#include <source_location>

// TODO: move this to a separate file
#define BHW_CONCAT(a, b) a##b

#define BHW_REFLECT_INTERNAL(class_name, var_name, ...) \
    namespace BHW \
    { \
        namespace __reflection \
        { \
            inline static const TypeInfo& BHW_CONCAT(__, var_name) = MakeTypeInfo<class_name, ##__VA_ARGS__>(std::source_location::current().file_name()); \
        } \
        template <> \
        inline auto Cast<TypeHash<class_name>()>(void* ptr) \
        { \
            return static_cast<class_name*>(ptr); \
        } \
        template <> \
        inline const TypeInfo& GetTypeInfo<TypeHash<class_name>()>() \
        { \
            return __reflection::BHW_CONCAT(__, var_name); \
        } \
        template <> \
        inline bool IsRegistered<class_name>() \
        { \
            return true; \
        } \
        template <> \
        inline const std::string_view& GetSourceLocation<TypeHash<class_name>()>() \
        { \
            return __reflection::BHW_CONCAT(__, var_name).SourceLocation; \
        } \
    }

#define BHW_REFLECT(class_name, ...) BHW_REFLECT_INTERNAL(class_name, __COUNTER__, ##__VA_ARGS__)

#define BHW_REFLECT_MEMBERS_INTERNAL(class_name, var_name, ...) \
    namespace BHW \
    { \
        namespace __reflection \
        { \
            inline static const auto BHW_CONCAT(__, var_name) = MakeMembers<class_name>(__VA_ARGS__); \
        } \
        template <> \
        inline auto GetMembers<TypeHash<class_name>()>() \
        { \
            return __reflection::BHW_CONCAT(__, var_name); \
        } \
    }

#define BHW_REFLECT_MEMBERS(class_name, ...) BHW_REFLECT_MEMBERS_INTERNAL(class_name, __COUNTER__, __VA_ARGS__)

#define BHW_REFLECT_MEMBER(member_name, member_ptr) MakeMember(member_name, member_ptr)