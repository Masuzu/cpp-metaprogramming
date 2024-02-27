#include <loop_unrolling.hpp>

#include <iostream>

#include <gtest/gtest.h>

TEST(LoopUnrolling, SimpleLoop)
{
    int counter = 0;
    unrolled_for_loop<int, 5>([&](auto index) { ++counter; });
    ASSERT_EQ(5, counter);
}
