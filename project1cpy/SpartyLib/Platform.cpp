/**
 * @file Platform.cpp
 * @author Omay Dogan
 */

#include "pch.h"
#include "Platform.h"
#include <math.h>
#include <wx/graphics.h>

/// Width of tiling images used in platform in pixels
const int tilingImageWidth = 32;

using namespace std;

/**
 * Constructor
 * @param game Game this platform is a member of
 * @param width Width of platform in pixels
 * @param height Height of platform in pixels
 * @param leftFilename Name of left end image file
 * @param centerFilename Name of center image file
 * @param rightFilename Name of right end image file
 */
Platform::Platform(Game *game, int width, int height, const std::wstring &leftFilename, const std::wstring &centerFilename, const std::wstring &rightFilename): Item(game, centerFilename)
{
    mWidth = width;
    mHeight = height;
    mLeftImage = make_unique<wxImage>(leftFilename, wxBITMAP_TYPE_ANY);
    mLeftBitmap = make_unique<wxBitmap>(*mLeftImage);
    mCenterImage = make_unique<wxImage>(centerFilename, wxBITMAP_TYPE_ANY);
    mCenterBitmap = make_unique<wxBitmap>(*mCenterImage);
    mRightImage = make_unique<wxImage>(rightFilename, wxBITMAP_TYPE_ANY);
    mRightBitmap = make_unique<wxBitmap>(*mRightImage);

}

/**
 * Draws the platform
 * @param graphics Graphics context on which platform is drawn
 * @param scale Scale for virtual pixel functionality
 */
void Platform::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale)
{
    double wid = GetWidth();
    double hit = GetHeight();

    for (int i = 0; i < ceil(GetWidth()/tilingImageWidth); i++)
    {
        if (i == 0)
        {
            graphics->DrawBitmap(*mLeftBitmap,
                                 int((GetX() - wid / 2) + i * tilingImageWidth),
                                 int(GetY() - hit / 2),
                                 int(tilingImageWidth + 1) , //The extra +1 is to eliminate rendering artifactslines
                                 int(hit) );
        }
        else if (i >= ceil(GetWidth()/tilingImageWidth) - 1)
        {
            graphics->DrawBitmap(*mRightBitmap,
                                 int((GetX() - wid / 2) + i * tilingImageWidth),
                                 int(GetY() - hit / 2),
                                 int(tilingImageWidth) ,
                                 int(hit) );
        }
        else
        {
            graphics->DrawBitmap(*mCenterBitmap,
                                 int((GetX() - wid / 2) + i * tilingImageWidth),
                                 int(GetY() - hit / 2),
                                 int(tilingImageWidth + 1), // The extra +1 is to fix rendering artifacts
                                 int(hit));
        }
    }
}
