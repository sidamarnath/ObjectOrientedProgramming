/**
 * @file AnimChannelPoint.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "AnimChannelPoint.h"

void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    auto keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);

}

void AnimChannelPoint::Tween(double t)
{
    mPoint = wxPoint(int(mKeyframe1->GetPoint().x + t * (mKeyframe2->GetPoint().x - mKeyframe1->GetPoint().x)),
            int(mKeyframe1->GetPoint().y + t * (mKeyframe2->GetPoint().y - mKeyframe1->GetPoint().y)));

}




