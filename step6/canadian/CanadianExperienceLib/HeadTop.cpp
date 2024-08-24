/**
 * @file HeadTop.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "HeadTop.h"
//#include "ImageDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 * @param filename The filename for the image
 */
HeadTop::HeadTop(const std::wstring &name, const std::wstring &filename) : ImageDrawable(name, filename)
{

}

/**
 * returns true if object is movable
 */
bool HeadTop::IsMovable()
{
    return true;
}

/**
 * Draws the head top
 * @param  graphics shared ptr to wxGraphics
 *
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);
    graphics->SetBrush(*wxBLACK_BRUSH);
    wxPoint p = TransformPoint(wxPoint(40, 75));
    wxPoint p1 = TransformPoint(wxPoint(70, 75));
    wxPoint p2 = TransformPoint(wxPoint(80, 60));
    wxPoint p3 = TransformPoint(wxPoint(65, 58));
    wxPoint p4 = TransformPoint(wxPoint(45, 58));
    wxPoint p5 = TransformPoint(wxPoint(30, 60));

    Eyes(p,graphics);
    Eyes(p1,graphics);
    Eyebrows(p2, p3, graphics);
    Eyebrows(p4, p5, graphics);


}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/** Function to create the eyes of the actor
* @param  e1 Point to transform
* @param  graphics wxGraphics used
*/
void HeadTop::Eyes(wxPoint e1, std::shared_ptr<wxGraphicsContext> graphics)
{
    float wid = 15.0f;
    float hit = 20.0f;

    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}


/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p1 Point to transform
* @param  p2 Point to transform
* @param  graphics Shared ptr to wxGraphics
*/
void HeadTop::Eyebrows(wxPoint p1, wxPoint p2, std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
}

