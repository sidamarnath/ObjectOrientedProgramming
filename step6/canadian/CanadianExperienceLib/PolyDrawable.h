/**
 * @file PolyDrawable.h
 * @author Sid Amarnath
 *
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"

//class Drawable;

/**
 * Draws polygons based on points
 */
class PolyDrawable : public Drawable {
private:
    /// The drawable name
    std::wstring mName;
    /// The polygon color
    wxColour mColor = *wxBLACK;
    /// The array of point objects
    std::vector<wxPoint> mPoints;
    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;

public:
    /// Destructor (virtual)
    virtual ~PolyDrawable() {}

    PolyDrawable(const std::wstring &name);

    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable &) = delete;

    /// Assignment operator (disabled)
    void operator=(const PolyDrawable &) = delete;

    /**
     * Sets picture for actor
     * @returns true to update the observer
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Checks whether we have hit an object
     * @param pos position of the point
     */
    bool HitTest(wxPoint pos) override;

    /**
     * Sets picture for actor
     * @param point point we are adding
     */
    void AddPoint(wxPoint point);

    /**
     * Get the polygon color
     * @return The polygon color
     */
    wxColor GetColor() const { return mColor; }

    /**
     * Set the color
    * @param color The new color
     */
    void SetColor(wxColor color) { mColor = color; }

};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
