/**
 * @file GrayCodeTest.cpp
 * @author Charles Owen
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <GrayCode.h>

TEST(GrayCodeTest, Increment)
{
    unsigned int code = 0;

    auto code1 = GrayCode::Increment(code);
    ASSERT_EQ(1, code1);

    auto code2 = GrayCode::Increment(code1);
    ASSERT_EQ(3, code2);

    unsigned int greys[] = {0, 1, 3, 2, 6, 7, 5, 4,
            12, 13, 15, 14, 10, 11, 9, 8};

    for (int i = 1; i<16; i++)
    {
        code = GrayCode::Increment(code);
        ASSERT_EQ(greys[i], code);
    }
}
