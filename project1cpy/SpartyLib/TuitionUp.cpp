/**
 * @file TuitionUp.cpp
 * @author Dean Eggenberger
 */

#include "pch.h"
#include "TuitionUp.h"
#include "Game.h"
#include <wx/graphics.h>

/// Float value for tuition increase
const float tuitionIncrease = 1.1;
/// Integer value for height
const static int Height = 1024;


/**
 * Constructor
 * @param game Game this TuitionUp is a member of
 * @param filename  filename
 */
TuitionUp::TuitionUp(Game *game, const std::wstring &filename) : Item(game, filename)
{

}

/**
 * Collision Test function.
 * @param item to test for collisions on
 * @return bool for if anything is colliding with item.
 */
bool TuitionUp::CollisionTest(Item* item)
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

    if(!collected)
    {
        auto game = Item::GetGame();
        game->TuitionIncrease(tuitionIncrease);
        collected = true;
        Item::SetRender(false);
    }

    return false;
}

/**
 * Function to reset the tuition up item to be in a collectable and visible state
 */
void TuitionUp::Reset()
{
    collected = false;
    SetLocation(GetX(), mStartHeight);
    Item::SetRender(true);
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param scale scale
 */
void TuitionUp::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale)
{
    Item::Draw(graphics, scale);

    if(collected)
    {
        wxFont font(wxSize(0, (Height * scale) * mTextScale / 24), wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL);
        graphics->SetFont(font, wxColour(0, 100, 0));
        graphics->DrawText(L"Tuition Increase!", GetX() + 5, GetY() + 5);

        if(mTextScale < 2.5)
        mTextScale += 0.05;
    }
}

/**
 * Handle updates in time of our gnome
 *
 * This is called before we draw and allows us to
 * move our gnome.
 * @param elapsed Time elapsed since the class call
 */
void TuitionUp::Update(double elapsed)
{
    double yLoc = GetY();

    if(collected)
    {
        if(yLoc >= -100)
        {
            SetLocation(GetX(), GetY() - 1000 * elapsed);
        }
    }
}

/**
 * Covid load Function.
 * @param node pointer for Xml file.
 */
void TuitionUp::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    mStartHeight = GetY();
}