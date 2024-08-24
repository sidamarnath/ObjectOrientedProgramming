/**
 * @file Wall.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "Wall.h"
#include <math.h>
#include <wx/graphics.h>

/// image height value
const int tilingImageHeight = 32;

/**
 * Constructor
 * @param game Game this wall is a member of
 */

Wall::Wall(Game *game, int width, int height, const std::wstring &filename) : Item(game, filename)
{
    mWidth = width;
    mHeight = height;
}

/**
 * Draws the wall
 * @param graphics Graphics context to draw wall to
 * @param scale Scale for virtual pixel functionality
 */
void Wall::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale)
{
    double wid = GetWidth();
    double hit = GetHeight();

    for (int i = 0; i < ceil(GetHeight()/tilingImageHeight); i++)
    {
        graphics->DrawBitmap(Item::GetBitmap(),
                             int(GetX() - wid / 2),
                             int(GetY() - hit / 2)  + i * tilingImageHeight,
                             wid,
                             tilingImageHeight + 1);
    }

}

