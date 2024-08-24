/**
 * @file Actor.h
 * @author Sid Amarnath
 *
 * Class for actors in our drawings.
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H


#include "AnimChannelPoint.h"

class Drawable;
class Picture;

/**
 * Class for the actors in our picture.
 */
class Actor {
private:
    /// The actor name
    std::wstring mName;

    /// Is this actor enabled (drawable)?
    bool mEnabled = true;

    /// The actor position
    wxPoint mPosition;

    /// Is this actor mouse clickable?
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// Picture variable
    Picture *mPicture = nullptr;

    /// Channel object from AnimChannelPoint
    AnimChannelPoint mChannel;


public:
    /// Destructor
    virtual ~Actor() {}

    /// Constructor
    Actor(const std::wstring &name);

    /// Default constructor (disabled)
    Actor() = delete;

    /// Copy constructor (disabled)
    Actor(const Actor &) = delete;

    /// Assignment operator
    void operator=(const Actor &) = delete;

    /// Set the root drawable for the actor
    void SetRoot(std::shared_ptr<Drawable> root);

    /// Draw this actor
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /// Test to see if a mouse click is on this actor.
    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    /// Adding a drawable to this actor
    void AddDrawable(std::shared_ptr<Drawable> drawable);


    /**
     * Get the actor name
     * @return Actor name
     */
    std::wstring GetName() const { return mName; }

    /**
     * The actor position
     * @return The actor position as a point
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @param pos The new actor position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }


    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor Enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /**
     * Gets picture for actor
     * @returns picture mPicture variable
     */
    Picture *GetPicture() {return mPicture;}

    //void SetPicture(Picture *picture) {mPicture = picture;}

    /**
     * Sets picture for actor
     * @param picture The picture we are working with
     * @returns the setter for the picture
     */
    void SetPicture(Picture *picture);

    void SetKeyframe();

    void GetKeyframe();

    /**
     * Get the position channel (for tests)
     * @return AnimChannelPoint object
     */
    AnimChannelPoint* GetPositionChannel() { return &mChannel;}





};

#endif //CANADIANEXPERIENCE_ACTOR_H
