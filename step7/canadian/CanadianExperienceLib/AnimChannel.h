/**
 * @file AnimChannel.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;


/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */

class AnimChannel {
private:
    /// The animation channel name
    std::wstring mName;

    /// pointer for keyframe1
    int mKeyframe1 = -1;

    /// pointer for keyframe2
    int mKeyframe2 = -1;

    /// The timeline object
    Timeline *mTimeline = nullptr;

protected:
    /// Default constructor
    AnimChannel() { }

    /**
    * Class that represents a keyframe
    */
    class Keyframe {
    private:
        /// frame for keyframe
        int mFrame;

        /// The channel this keyframe is associated with
        AnimChannel *mChannel;

    protected:
        /**
         * Constructor
        * @param channel the channel this keyframe is associated with
        */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    public:

        /**
        * Use as one function set to 0 in base class
        */
        virtual void UseAs1() = 0;
        /**
        * Use as two function set to 0 in base class
        */
        virtual void UseAs2() = 0;
        /**
        * Use as only function set to 0 in base class
        */
        virtual void UseOnly() = 0;

        /**
        * Gets the frame
        * @returns the frame
        */
        int GetFrame() {return mFrame;}

        /**
        * Sets the frame
        * @param frame the new frame
         * @return new frame
        */
        void SetFrame(int frame) {mFrame = frame;}
    };
    /**
     * Inserts the keyframe
     * @param keyframe keyframe to insert
     */
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Makes transition between keyframes more smooth
     * @param t time
     */
    virtual void Tween(double t) {};


private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:
    /// Destructor
    virtual ~AnimChannel() {}
    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;

    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    /**
     * checks if valid
     * @return true depending on idx of keyframes
     */
    bool IsValid();

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
    void SetFrame(int currFrame);

    /**
     * Get the position channel (for tests)
     * @return AnimChannelPoint object
     */
    std::wstring GetName() {return mName;}

    /**
     * Set the name of AnimChannel
     * @param name new name
     * @return the new name
     */
    void SetName(std::wstring name) {mName = name;}

    /**
     * Get the timeline from timeline
     * @return timeline object
     */
    Timeline *GetTimeline() {return mTimeline;}

    /**
     * Sets the timeline channel
     * @param timeline timeline object
     * @return new timeline
     */
    void SetTimeline(Timeline *timeline) {mTimeline = timeline; }

    /**
     * Deletes an AnimChannel keyframe
     * @return AnimChannelPoint object
     */
    void DeleteKeyframe();


};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
