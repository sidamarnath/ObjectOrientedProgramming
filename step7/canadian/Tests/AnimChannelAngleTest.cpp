/**
 * @file AnimChannelAngleTest.cpp
 * @author Sid Amarnath
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>
//#include <AnimChannel.h>

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle channel;
    channel.SetName(L"Sid");
    ASSERT_EQ(L"Sid", channel.GetName());

}