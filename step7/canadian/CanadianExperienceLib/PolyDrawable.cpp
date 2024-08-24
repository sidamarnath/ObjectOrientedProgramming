/**
 * @file PolyDrawable.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "PolyDrawable.h"
#include "Drawable.h"

/**
 * Constructor
 * @param name The drawable name
 */
PolyDrawable::PolyDrawable(const std::wstring &name) : Drawable(name)
{

}

/**
 * Constructor
 * @param graphics shared ptr to wxGraphics
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty())
    {

        auto path = graphics->CreatePath();
        path.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            path.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        path.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(path);
    }

    mPath = graphics->CreatePath();
    mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
    for (auto i = 1; i<mPoints.size(); i++)
    {
        mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
    }
    mPath.CloseSubpath();
}

/**
* Test to see if a mouse click is on this actor.
* @param pos Mouse position on drawing
* @return A bool (false) if we missed, true otherwise.
*/
bool PolyDrawable::HitTest(wxPoint pos)
{
    return mPath.Contains(pos.x, pos.y);
}

/**
 * Adds point at end of the list of points
 * @param point The drawable name
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}