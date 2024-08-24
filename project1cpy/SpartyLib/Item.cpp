/**
 * @file Item.cpp
 *
 * @author Kathryn Nagy
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <memory>
#include <wx/xml/xml.h>
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor for item
 * @param game Game to which item belongs
 * @param filename Name of image file
 */
Item::Item(Game* game, const std::wstring &filename) : mGame(game)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage); // This causes an additional error if the image cannot be loaded
}

/**
 * Draw the item to the screen
 * @param graphics Graphics context to draw to
 * @param scale Scale for virtual pixel functionality
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics, double scale)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    if (mRender) graphics->DrawBitmap(*mItemBitmap,
            ( (int)GetX() - wid / 2) ,
            ( (int)GetY() - hit / 2),
            wid + 1,
            hit );
}

/**
 * Destructor for item class
 */
Item::~Item()
{

}


void Item::XmlLoad(wxXmlNode *node)
{

    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);

}

/**
 * Test if there is a collision between items
 * @param item Item to test collision with
 * @return bool if collide
 */
bool Item::CollisionTest(Item* item)
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetWidth() / 2;
    auto itemRight = item->GetX() + item->GetWidth() / 2;
    auto itemTop = item->GetY() - item->GetHeight() / 2;
    auto itemBottom = item->GetY() + item->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two items
    if (ourRight < itemLeft ||  // Completely to the left
            ourLeft > itemRight ||  // Completely to the right
            ourTop > itemBottom ||  // Completely below
            ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}


void Item::SetBitmap(const std::wstring &filename)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage); // This causes an additional error if the image cannot be loaded
}

/**
 * @return mGame float mTuitionMultiplier of mGame for animation rendering
 */
 float Item::GameTuitionMultiplier()
 {
     return mGame->GetTuitionMultiplier();
 }
