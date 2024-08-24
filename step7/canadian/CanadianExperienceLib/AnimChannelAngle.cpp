/**
 * @file AnimChannelAngle.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "AnimChannelAngle.h"


void AnimChannelAngle::SetKeyframe(double angle)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    auto keyframe = std::make_shared<KeyframeAngle>(this, angle);

    // Insert it into the collection
    InsertKeyframe(keyframe);

}

/**
 * Compute an angle that is an interpolation
 * between two keyframes
 *
 * This function is called after Use1 and Use2,
 * so we have pointers to valid keyframes of the
 * type KeyframeAngle. This function computes the
 * tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelAngle::Tween(double t)
{
    mAngle = mKeyframe1->GetAngle() * (1 - t) +
            mKeyframe2->GetAngle() * t;
}


