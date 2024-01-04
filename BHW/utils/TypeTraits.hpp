#pragma once

#include <type_traits>

namespace BHW
{
    template <template <typename...> class Template, typename T>
    struct is_specialization_of : std::false_type {};

    template <template <typename...> class Template, typename... Args>
    struct is_specialization_of<Template, Template<Args...>> : std::true_type {};

    template <template <typename...> class Template, typename T>
    constexpr bool is_specialization_of_v = is_specialization_of<Template, T>::value;

    template <typename TBase, typename TDerived>
    struct is_base_of_specialization_of : std::false_type {};

    template <template <typename...> class Template, typename TBase, typename... Args>
    struct is_base_of_specialization_of<TBase, Template<Args...>> : std::is_base_of<TBase, Template<Args...>> {};

    template <typename TBase, typename TDerived>
    constexpr bool is_base_of_specialization_of_v = is_base_of_specialization_of<TBase, TDerived>::value;
}