/**
 * @file AnimChannelAngle.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"


/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:
    /// angle member variable for channel
    double mAngle = 0;

protected:

    /**
    * Class that represents a keyframe angle
    */
    class KeyframeAngle : public Keyframe {
    private:
        /// angle member variable for keyframe angle
        double mAngle;
        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    public:
        /**
        * Constructor
         * @param channel the channel object
         * @param angle the angle
        */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}
        /// Default constructor (disabled)
        KeyframeAngle() = delete;

        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;

        /// Assignment operator
        void operator=(const KeyframeAngle &) = delete;

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
        void UseOnly() override {mChannel->mAngle = mAngle;}

        /**
        * Getter for the angle
         * @return the angle
        */
        double GetAngle() {return mAngle;}
    };

        /**
        * Makes transition between keyframes smooth
         * @param t time
        */
    void Tween(double t);

private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelAngle() { }

    /// Destructor
    virtual ~AnimChannelAngle() {}

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;

    /**
    * Sets the keyframe
    * @param angle the angle
    */
    void SetKeyframe(double angle);

    /**
    * Getter for the angle for the channel class
    * @return the angle
    */
    double GetAngle() {return mAngle;}

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
