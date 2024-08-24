/**
 * @file AnimChannel.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "AnimChannel.h"
#include "Timeline.h"

bool AnimChannel::IsValid()
{
    return mKeyframe1 >= 0 || mKeyframe2 >= 0;
}

/**
 * Ensure the keyframe indices are valid for the current time.
 *
 * The location pointed to by keyframe1 must be a time less than or
 * equal to the current time and the location pointed to by keyframe2
 * must be the next location and a location greater than the current
 * time. Note that the time may be before or after the first or last
 * item in the list.  We indicate that with values of -1 for the
 * indices.
 * @param currFrame The frame we are on.
 */
void AnimChannel::SetFrame(int currFrame)
{
    // Should we move forward in time?
    while (mKeyframe2 >= 0 && mKeyframes[mKeyframe2]->GetFrame() <= currFrame)
    {
        mKeyframe1 = mKeyframe2;
        mKeyframe2++;
        if (mKeyframe2 >= (int)mKeyframes.size())
            mKeyframe2 = -1;
    }

    // Should we move backwards in time?
    while (mKeyframe1 >= 0 && mKeyframes[mKeyframe1]->GetFrame() > currFrame)
    {
        mKeyframe2 = mKeyframe1;
        mKeyframe1--;
    }

    //
    // There are four possibilities here:
    // a) No keyframes  (mKeyframe1 < 0 and mKeyframe2 < 0)
    // b) Only a keyframe to the left (mKeyframe1 >= 0 and mKeyframe2 < 0)
    // c) Between two keyframes (mKeyframe1 >= 0 and mKeyframe2 >= 0)
    // d) Only a keyframe to the right (mKeyframe1 < 0 and mKeyframe2 >= 0)
    //
    if (mKeyframe1 >= 0 && mKeyframe2 >= 0)
    {
        // c) Between two keyframes
        // So we have to tween
        mKeyframes[mKeyframe1]->UseAs1();
        mKeyframes[mKeyframe2]->UseAs2();

        // Compute the t value
        double frameRate = GetTimeline()->GetFrameRate();
        double time1 = mKeyframes[mKeyframe1]->GetFrame() / frameRate;
        double time2 = mKeyframes[mKeyframe2]->GetFrame() / frameRate;
        double t = (GetTimeline()->GetCurrentTime() - time1) / (time2 - time1);

        // And tween
        Tween(t);
    }
    else if (mKeyframe1 >= 0)
    {
        // b) Only a keyframe to the left
        // We are only using keyframe 1
        mKeyframes[mKeyframe1]->UseOnly();
    }
    else if (mKeyframe2 >= 0)
    {
        // d) Only a keyframe to the right
        // We are only using keyframe 2
        mKeyframes[mKeyframe2]->UseOnly();
    }

}

void AnimChannel::InsertKeyframe(std::shared_ptr<Keyframe> keyframe)
{
    // Get the current frame and tell it to the keyframe we are setting.
    int currFrame = mTimeline->GetCurrentFrame();
    keyframe->SetFrame(currFrame);

    // The possible options for keyframe insertion
    enum { Append, Replace, Insert } action;

    // Determine the action we will do
    if (mKeyframe1 < 0)
    {
        // There is no first keyframe. This means
        // we are before any keyframes or there are no keyframes.
        // If before a keyframe, we insert, otherwise, we append
        action = mKeyframe2 >= 0 ? Insert : Append;
    }
    else
    {
        // We know mKeyframe1 is valid
        // So, we are after it.
        int frame1 = mKeyframes[mKeyframe1]->GetFrame();

        if (mKeyframe2 < 0)
        {
            // There is no second keyframe.
            // If we are after the current frame, we append.
            // If we are on the current frame, we replace.
            action = frame1 < currFrame ? Append : Replace;
        }
        else
        {
            // There is a second keyframe
            // If we are before the first frame, we insert
            // If not, we replace
            action = frame1 < currFrame ? Insert : Replace;
        }
    }

    //
    // And do the appropriate action
    //
    switch (action)
    {
    case Append:
        // Add to end and the keyframe to the left becomes the new keyframe
        mKeyframes.push_back(keyframe);
        mKeyframe1 = (int)mKeyframes.size() - 1;
        break;

    case Replace:
        // Replace the current keyframe
        mKeyframes[mKeyframe1] = keyframe;
        break;

    case Insert:
        // Insert after mKeyframe1
        // and mKeyframe1 becomes this new insertion (frame we are on)
        mKeyframes.insert(mKeyframes.begin() + (mKeyframe1 + 1), keyframe);
        mKeyframe1++;
        break;
    }

}

void AnimChannel::DeleteKeyframe()
{
    if ((mKeyframe1 < 0) && (mKeyframe2 < 0))
    {
        return;
    }

    if ((mKeyframe1 == 0) && (mKeyframe2 <= 0))
    {
        auto location3 = find(std::begin(mKeyframes), std::end(mKeyframes),
                mKeyframes[mKeyframe1]);
        mKeyframes.erase(location3);
        mKeyframe1--;

    }

    if ((mKeyframe1 >= 0) && (mKeyframe2 >= 0))
    {
        auto location = find(std::begin(mKeyframes), std::end(mKeyframes),
                mKeyframes[mKeyframe1]);
        mKeyframes.erase(location);
        mKeyframe1--;
        mKeyframe2--;
    }

    if ((mKeyframe1 > 0) && (mKeyframe2 < 0))
    {
        auto location2 = find(std::begin(mKeyframes), std::end(mKeyframes),
                mKeyframes[mKeyframe1]);
        mKeyframes.erase(location2);
        mKeyframe1--;
    }
}

