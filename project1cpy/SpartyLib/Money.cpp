/**
 * @file Money.cpp
 * @author Omay
 */

#include "pch.h"
#include "Money.h"
#include "Game.h"
#include <wx/graphics.h>

using namespace std;

//const std::wstring moneyImageName = L"../images/Money100.png";

/// Game area height in virtual pixels
const static int Height = 1024;


Money::Money(Game* game, const std::wstring &filename, int amount) : Item(game, filename)
{
    mAmount = amount;
}

/**
 * Collision Test function.
 * @param item to test for collisions on
 * @return bool for if anything is colliding with item.
 */
bool Money::CollisionTest(Item* item)
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

    if(!mCollected)
    {
        auto game = Item::GetGame();
        game->CollectedMoney(mAmount);
        mCollected = true;
        //Item::SetRender(false);
    }

    return false;
}

/**
 * Handle updates in time of our gnome
 *
 * @param elapsed Time elapsed since the class call
 */
void Money::Update(double elapsed)
{
    double yLoc = GetY();

    if(mCollected)
    {
        if(yLoc >= -60)
        {
            SetLocation(GetX(), GetY() - 800 * elapsed);
        }
    }
}

/**
 * Covid load Function.
 * @param node pointer for Xml file.
 */
void Money::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    mStartHeight = GetY();
}

/**
 * Function that resets the moneys position and allows it to be redrawn on screen and collectable
 */
void Money::Reset()
{
    mCollected = false;
    SetLocation(GetX(), mStartHeight);
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param scale scale
 */
void Money::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale)
{
    Item::Draw(graphics, scale);

    if(mCollected)
    {
        wxFont font(wxSize(0, (Height * scale) / 24), wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL);
        graphics->SetFont(font, wxColour(26, 101, 42));
        graphics->DrawText(L"+" + to_string(int(mAmount * Item::GameTuitionMultiplier())), GetX() + 5, GetY() + 5);
    }
}
