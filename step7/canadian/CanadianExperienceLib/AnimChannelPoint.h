/**
 * @file AnimChannelPoint.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOINT_H

#include "AnimChannel.h"

/**
 * Animation channel for points.
 */
class AnimChannelPoint : public AnimChannel {
private:
    /// point variable for channel
    wxPoint mPoint = wxPoint(0,0);


protected:
    /**
    * Class that represents a keyframe point
    */
    class KeyframePoint : public Keyframe {
    private:
        /// point variable for keyframe
        wxPoint mPoint;

        /// The channel this keyframe is associated with
        AnimChannelPoint *mChannel;


    public:
        /**
        * Constructor
         * @param channel the channel object
         * @param point the point
        */
        KeyframePoint(AnimChannelPoint *channel, wxPoint point) :
        Keyframe(channel), mChannel(channel), mPoint(point) {}

        /// Default constructor (disabled)
        KeyframePoint() = delete;

        /// Copy constructor (disabled)
        KeyframePoint(const KeyframePoint &) = delete;

        /// Assignment operator
        void operator=(const KeyframePoint &) = delete;

        /**
        * Use as one function (overridden)
        */
        void UseAs1() override {mChannel->mKeyframe1 = this;}
        /**
        * Use as two function (overridden)
        */
        void UseAs2() override {mChannel->mKeyframe2 = this;}
        /**
        * Use as only function (overridden)
        */
        void UseOnly() override {mChannel->mPoint = mPoint;}

        /**
        * Gets the point
         * @return the point
        */
        wxPoint GetPoint() {return mPoint;}

    };

    /**
    * Makes the transition between keyframes smooth (overridden)
     * @param t the time
    */
    void Tween(double t) override;

private:
    /// The first point keyframe
    KeyframePoint *mKeyframe1 = nullptr;

    /// The second point keyframe
    KeyframePoint *mKeyframe2 = nullptr;

public:

    /// Default constructor
    AnimChannelPoint() { }

    /// Destructor
    virtual ~AnimChannelPoint() {}

    /// Copy constructor (disabled)
    AnimChannelPoint(const AnimChannelPoint &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelPoint &) = delete;

    /**
    * Sets the keyframe
     * @param point the current point
    */
    void SetKeyframe(wxPoint point);

    /**
    * Gets the point for channel
     * @returns the point
    */
    wxPoint GetPoint() {return mPoint;}


};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
