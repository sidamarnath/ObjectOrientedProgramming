/**
 * @file HeadTop.h
 * @author Sid Amarnath
 *
 * Class for creating the eyes and eyebrows of the top head
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"
#include "AnimChannelPoint.h"
#include "Timeline.h"
//#include "Drawable.h"

/**
 * Class for creating the eyes and eyebrows of the top head
 */
class HeadTop : public ImageDrawable {
private:
    /// The channel this head top is associated with
    AnimChannelPoint mChannel;


public:
    /// Destructor (virtual)
    virtual ~HeadTop() {}
    /// Default constructor (disabled)
    HeadTop() = delete;

    /// Copy constructor (disabled)
    HeadTop(const HeadTop &) = delete;

    /// Assignment operator (disabled)
    void operator=(const HeadTop &) = delete;

    /// Constructor
    HeadTop(const std::wstring &name, const std::wstring &filename);

    /**
     * Decides whether the object is movable
    * @returns true or false depending on success
     */
    bool IsMovable() override;

    /// Draws the features of the head top
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Transforms the point
     *  @returns Transformed point
     */
    wxPoint TransformPoint(wxPoint p);

    /** Function to create the eyes of the actor
    * @param  e1 Point to transform
    * @param  graphics wxGraphics used
    */
    void Eyes(wxPoint e1, std::shared_ptr<wxGraphicsContext> graphics);

    /** Transform a point from a location on the bitmap to
    *  a location on the screen.
    * @param  p1 Point to transform
    * @param  p2 Point to transform
    * @param  graphics Shared ptr to wxGraphics
    */
    void Eyebrows(wxPoint p1, wxPoint p2, std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Sets the keyframe for head top (overridden)
    */
    virtual void SetKeyframe() override;

    /**
     * Gets the keyframe for head top (overridden)
    */
    virtual void GetKeyframe() override;

    /**
     * Sets the timeline for head top (overridden)
     * @param timeline the timeline object
    */
    virtual void SetTimeline(Timeline* timeline) override;













};

#endif //CANADIANEXPERIENCE_HEADTOP_H
