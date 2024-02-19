#ifndef _PARAMETER_PACK_UTILS_HPP
#define _PARAMETER_PACK_UTILS_HPP

#include <tuple>
#include <type_traits>

namespace parameter_pack
{
    template <typename... T>
    struct first;

    template <typename T, typename... Rest>
    struct first<T, Rest...>
    {
        using type = T;
    };

    template <typename Element, template <Element...> typename Container, Element first_value, Element... rest>
    struct first<Container<first_value, rest...>>
    {
        using type = Element;
        static constexpr Element value = first_value;
    };

    template <auto first, auto... rest>
    struct first_value
    {
        static constexpr auto value = first;
    };

    template <typename... T>
    struct last;

    template <typename... T>
    struct last
    {
        using type = typename decltype((std::type_identity<T>{}, ...))::type;
    };

    template <typename T>
    struct last<T>
    {
        using type = T;
    };

    template <typename Element, template <Element...> typename Container, Element... element>
    struct last<Container<element...>>
    {
        using type = Element;
        static constexpr Element value = (element, ...);
    };

    template <auto... element>
    struct last_value
    {
        static constexpr auto value = (element, ...);
    };

    template <unsigned int n, typename... T>
    struct at;

    template <unsigned int n, typename... T>
    struct at
    {
        using type = std::tuple_element<n, std::tuple<T...>>::type;
    };

    template <unsigned int n, typename Element, template <Element...> typename Container, Element... element>
    struct at<n, Container<element...>>
    {
        using type = Element;
        static constexpr Element value = std::get<n>(std::tuple{element...});
    };

    namespace distinct
    {
        template <typename Element, template <Element...> typename Container, Element integral_constant, Element... element>
        constexpr auto operator+(Container<element...> vector, std::integral_constant<Element, integral_constant> element_to_add)
        {
            if constexpr (sizeof...(element) == 0)
            {
                return Container<integral_constant>{};
            }
            else if constexpr (last_value<element...>::value == element_to_add)
            {
                return vector;
            }
            else
            {
                return Container<element..., integral_constant>{};
            }
        }

        template <typename Container>
        struct of;

        template <typename Element, template <Element...> typename Container, Element... element>
        struct of<Container<element...>>
        {
            using type = decltype((Container<>{} + ... + std::integral_constant<Element, element>{}));
        };
    }

    template <typename Element, template <Element...> typename Container, Element... elementA, Element... elementB>
    constexpr auto concat(Container<elementA...>, Container<elementB...>)
    {
        return Container<elementA..., elementB...>{};
    };

    template <typename Element, template <Element...> typename Container, Element... element, unsigned int... indices>
    constexpr auto copy_indices(Container<element...>, std::integer_sequence<unsigned int, indices...>)
    {
        return Container<parameter_pack::at<indices, Container<element...>>::value...>{};
    };

    template <unsigned int offset, unsigned int... indices>
    constexpr auto add_offset(std::integer_sequence<unsigned int, indices...>)
    {
        return std::integer_sequence<unsigned int, (offset + indices)...>{};
    }

    template <unsigned int offset, unsigned int n>
    constexpr auto make_index_sequence_with_offset()
    {
        return add_offset<offset>(std::make_integer_sequence<unsigned int, n>{});
    }

    namespace swap_details
    {
        template <unsigned int i, unsigned int j, typename Element, template <Element...> typename Container, Element... elements>
        constexpr auto swap(std::integral_constant<unsigned int, i>, std::integral_constant<unsigned int, j>, Container<elements...> container)
        {
            if constexpr (i == j)
            {
                return container;
            }
            else
            {
                constexpr std::tuple tuple{elements...};
                constexpr auto min_index = i < j ? i : j;
                constexpr auto max_index = i > j ? i : j;
                constexpr auto first_half = concat(
                    copy_indices(container, std::make_integer_sequence<unsigned int, min_index>{}),
                    Container<std::get<max_index>(tuple)>{});
                constexpr auto second_half = concat(
                    first_half,
                    copy_indices(container, make_index_sequence_with_offset<min_index + 1, max_index - min_index - 1>()));
                constexpr auto container_with_both_swapped_elements = concat(
                    second_half,
                    Container<std::get<min_index>(tuple)>{});
                constexpr auto remaining_element_count = (sizeof...(elements)) - max_index - 1;
                constexpr auto result = concat(
                    container_with_both_swapped_elements,
                    copy_indices(container, make_index_sequence_with_offset<max_index + 1, remaining_element_count>()));
                return result;
            }
        };
    }

    template <unsigned int i, unsigned int j, typename Container>
    struct swap;

    template <unsigned int i, unsigned int j, typename Element, template <Element...> typename Container, Element... elements>
    struct swap<i, j, Container<elements...>>
    {
        using type = decltype(swap_details::swap(std::integral_constant<unsigned int, i>{}, std::integral_constant<unsigned int, j>{}, Container<elements...>{}));
    };
}

#endif
