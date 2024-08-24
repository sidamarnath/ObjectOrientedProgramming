/**
 * @file Villain.cpp
 * @author Dean Eggenberger
 */

#include "pch.h"
#include "Villain.h"
#include "Game.h"


Villain::Villain(Game* game, const std::wstring &filename) : Item(game, filename)
{

}

/**
 * Handle updates in time of our gnome
 *
 * This is called before we draw and allows us to
 * move our gnome.
 * @param elapsed Time elapsed since the class call
 */
void Villain::Update(double elapsed)
{
    double yLoc = GetY();

    if(mGoingUp)
    {
        if(yLoc <= mStartHeight - 300)
        {
            mGoingUp = false;
        }
        else
        {
            SetLocation(GetX(), GetY() - 300 * elapsed / 1.250);
        }
    }
    else
    {
        if(yLoc >= mStartHeight)
        {
            mGoingUp = true;
        }
        else
        {
            SetLocation(GetX(), GetY() + 300 * elapsed / 1.250);
        }
    }
}

/**
 * Covid load Function.
 * @param node pointer for Xml file.
 */
void Villain::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    mStartHeight = GetY();
}

/**
 * Collision Test function.
 * @param item to test for collisions on
 * @return bool for if anything is colliding with item.
 */
bool Villain::CollisionTest(Item* item)
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
    game->GnomeDeath();

    return false;
}

