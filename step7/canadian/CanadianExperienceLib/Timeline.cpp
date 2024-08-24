/**
 * @file Timeline.cpp
 * @author Sid Amarnath
 *
 * This class implements a timeline that manages the animation
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
 * Constructor
 */
Timeline::Timeline()
{

}

void Timeline::AddChannel(AnimChannel* channel)
{
    mChannels.push_back(channel);
    channel->SetTimeline(this);

}


void Timeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}

void Timeline::DeleteKeyframe()
{
    for (auto channel : mChannels)
    {
        channel->DeleteKeyframe();
    }

}