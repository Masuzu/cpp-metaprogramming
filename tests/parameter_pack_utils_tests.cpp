#include <parameter_pack_utils.hpp>

#include <gtest/gtest.h>

template<char... element>
struct CharVector
{
};

template<int... element>
struct IntVector
{
};

TEST(ParameterPackUtils, First)
{
    static_assert(std::is_same<parameter_pack::first<int>::type, int>::value);
    static_assert(std::is_same<parameter_pack::first<const int&>::type, const int&>::value);
    static_assert(std::is_same<parameter_pack::first<char, int>::type, char>::value);
    static_assert(std::is_same<parameter_pack::first<char, const int&>::type, char>::value);

    static_assert(std::is_same<parameter_pack::first<IntVector<1, 2, 3>>::type, int>::value);
    static_assert(parameter_pack::first<IntVector<1, 2, 3>>::value == 1);

    static_assert(std::is_same<parameter_pack::first<CharVector<'d', 'a', 'c'>>::type, char>::value);
    static_assert(parameter_pack::first<CharVector<'d', 'a', 'c'>>::value == 'd');

    static_assert(parameter_pack::first_value<1, 2, 'c'>::value == 1);
    static_assert(parameter_pack::first_value<'d', 'a', 'c'>::value == 'd');
}

TEST(ParameterPackUtils, Last)
{
    static_assert(std::is_same<parameter_pack::last<int>::type, int>::value);
    static_assert(std::is_same<parameter_pack::last<const int&>::type, const int&>::value);
    static_assert(std::is_same<parameter_pack::last<char, int>::type, int>::value);
    static_assert(std::is_same<parameter_pack::last<char, const int&>::type, const int&>::value);

    static_assert(std::is_same<parameter_pack::last<IntVector<1, 2, 3>>::type, int>::value);
    static_assert(parameter_pack::last<IntVector<1, 2, 3>>::value == 3);

    static_assert(std::is_same<parameter_pack::last<CharVector<'d', 'a', 'c'>>::type, char>::value);
    static_assert(parameter_pack::last<CharVector<'d', 'a', 'c'>>::value == 'c');

    static_assert(parameter_pack::last_value<1, 2, 3>::value == 3);
    static_assert(parameter_pack::last_value<1, 2, '3'>::value == '3');
}

TEST(ParameterPackUtils, At)
{
    static_assert(std::is_same<parameter_pack::at<0, int>::type, int>::value);
    static_assert(std::is_same<parameter_pack::at<2, int, char, int&&>::type, int&&>::value);

    static_assert(parameter_pack::at<1, IntVector<1, 2, 3>>::value == 2);
    static_assert(parameter_pack::at<1, CharVector<'d', 'a', 'c'>>::value == 'a');
}

TEST(ParameterPackUtils, Distinct)
{
    static_assert(std::is_same<parameter_pack::distinct::of<IntVector<1, 1, 2, 3, 3, 4>>::type, IntVector<1, 2, 3, 4>>::value);
}

TEST(ParameterPackUtils, Swap)
{
    static_assert(std::is_same_v<parameter_pack::swap<3, 4, IntVector<1, 2, 3, 4, 5>>::type, IntVector<1, 2, 3, 5, 4>>);
    static_assert(std::is_same_v<parameter_pack::swap<1, 3, IntVector<1, 2, 3, 4, 5>>::type, IntVector<1, 4, 3, 2, 5>>);
    static_assert(std::is_same_v<parameter_pack::swap<3, 1, IntVector<1, 2, 3, 4, 5>>::type, IntVector<1, 4, 3, 2, 5>>);
    static_assert(std::is_same_v<parameter_pack::swap<3, 3, IntVector<1, 2, 3, 4, 5>>::type, IntVector<1, 2, 3, 4, 5>>);
}
