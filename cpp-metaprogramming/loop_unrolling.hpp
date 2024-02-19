#ifndef _LOOP_UNROLLING_HPP
#define _LOOP_UNROLLING_HPP

#include <type_traits>
#include <utility>

namespace detail
{
    template <typename Index, Index... indices, typename Method>
    void unrolled_for_loop(std::integer_sequence<Index, indices...>, Method &&method)
    {
        (method(std::integral_constant<Index, indices>{}), ...);
    }
}

template <typename Index, Index count, typename Method>
void unrolled_for_loop(Method &&method)
{
    detail::unrolled_for_loop(std::make_integer_sequence<Index, count>{}, std::forward<Method>(method));
}

#endif
