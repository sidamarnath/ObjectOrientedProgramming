/**
 * @file TimelineTest.cpp
 * @author Sid Amarnath
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>
#include <AnimChannelAngle.h>

TEST(TimelineTest, NumFrames)
{
    Timeline timeline;
    auto frame = timeline.GetNumFrames();
    ASSERT_EQ(300, timeline.GetNumFrames());
    auto newFrame = 350;
    timeline.SetNumFrames(newFrame);
    ASSERT_EQ(timeline.GetNumFrames(), newFrame);
}

TEST(TimelineTest, FrameRate)
{
    Timeline timeline;
    auto frameRate = timeline.GetFrameRate();
    ASSERT_EQ(30, timeline.GetFrameRate());
    auto newFrameRate = 350;
    timeline.SetFrameRate(newFrameRate);
    ASSERT_EQ(timeline.GetFrameRate(), newFrameRate);

}

TEST(TimelineTest, CurrentTime)
{
    Timeline timeline;
    auto time = timeline.GetCurrentTime();
    ASSERT_NEAR(0, time, 0.00001);
    double newTime = 350;
    timeline.SetCurrentTime(newTime);
    ASSERT_NEAR(timeline.GetCurrentTime(), newTime, 0.00001);

}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}