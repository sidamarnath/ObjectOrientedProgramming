/**
 * @file Covid.cpp
 * @author Dean Eggenberger
 */

#include "pch.h"
#include "Covid.h"
#include "Game.h"


Covid::Covid(Game* game, const std::wstring &filename) : Item(game, filename)
{

}

/**
 * Update the item
 * @param elapsed time since last frame
 */
void Covid::Update(double elapsed)
{
    double xLoc = GetX();

    if(mGoingLeft)
    {
        if(xLoc <= mStartX - 800)
        {
            mGoingLeft = false;
        }
        else
        {
            SetLocation(GetX() - 800 * elapsed / 3.6, GetY());
        }
    }
    else
    {
        if(xLoc >= mStartX)
        {
            mGoingLeft = true;
        }
        else
        {
            SetLocation(GetX() + 800 * elapsed / 3.6, GetY());
        }
    }
}

/**
 * Covid load Function.
 * @param node pointer for Xml file.
 */
void Covid::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    mStartX = GetX();
}

/**
 * Collision Test function.
 * @param item to test for collisions on
 * @return bool for if anything is colliding with item.
 */
bool Covid::CollisionTest(Item* item)
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

    auto game = Item::GetGame();
    game->GnomeFreeze();

    return true;
}