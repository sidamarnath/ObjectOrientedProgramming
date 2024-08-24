/**
 * @file ImageDrawable.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"

/// Class to draw the image needed
class ImageDrawable : public Drawable {
private:
    /// The actor name
    std::wstring mName;
    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// Center point we will use
    wxPoint mCenter;

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

public:
    /// Destructor (virtual)
    virtual ~ImageDrawable() {}
    /// Default constructor (disabled)
    ImageDrawable() = delete;

    /// Copy constructor (disabled)
    ImageDrawable(const ImageDrawable &) = delete;

    /// Assignment operator (disabled)
    void operator=(const ImageDrawable &) = delete;

    /**
     * Constructor
     * @param name name of image drawable
     * @param filename name of file for image
     */
    ImageDrawable(const std::wstring &name, const std::wstring &filename);

    /**
     * Draws this actor
     * @param graphics shared ptr to wxGraphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Sets picture for actor
     * @param pos position of point
     * @returns true if we have hit an object
     */
    bool HitTest(wxPoint pos);

    /**
     * Get the image name
     * @return image name
     */
    //std::wstring GetName() const { return mName; }

    /**
     * The image center
     * @return The image center as a point
     */
    wxPoint GetCenter() const { return mCenter; }

    /**
     * The image center
     * @param pos The new image center
     */
    void SetCenter(wxPoint pos) { mCenter = pos; }

};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
