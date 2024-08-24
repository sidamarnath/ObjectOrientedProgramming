/**
 * @file Picture.h
 * @author Sid Amarnath
 *
 *
 */

#include <vector>

#ifndef CANADIANEXPERIENCE_PICTURE_H
#define CANADIANEXPERIENCE_PICTURE_H

class PictureObserver;
class Actor;

/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// The actors in this picture
    std::vector<std::shared_ptr<Actor> > mActors;

public:
    Picture() {}

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;

    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    /**
     * Adds an observer
     * @param observer observer we are adding
     */
    void AddObserver(PictureObserver *observer);

    /**
     * Adds an observer
     * @param observer observer we are adding
     */
    void RemoveObserver(PictureObserver *observer);

    /**
     * Adds an observer
     */
    void UpdateObservers();

    /**
     * Draws the picture
     * @param graphics shared ptr to wxGraphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Adds an actor
     * @param actor actor we are adding
     */
    void AddActor(std::shared_ptr<Actor> actor);

    /** Iterator that iterates over the actors in the picture */
    class ActorIter
    {
    public:
        /** Constructor
         * @param picture The picture we are iterating over
         * @param pos Position in the collection
         */
        ActorIter(Picture* picture, int pos) : mPicture(picture), mPos(pos) {}

        /**
         * Compare two iterators
         * @param other The other iterator we are comparing to
         * @return  true if this position is not equal to the other position
        */
        bool operator!=(const ActorIter& other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Actor> operator *() const { return mPicture->mActors[mPos]; }

        /**
         * Increment the iterator
         * @return Reference to this iterator */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        Picture* mPicture;   ///< Picture we are iterating over
        int mPos;       ///< Position in the collection
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    ActorIter begin() { return ActorIter(this, 0); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    ActorIter end() { return ActorIter(this, mActors.size()); }

};

#endif //CANADIANEXPERIENCE_PICTURE_H
