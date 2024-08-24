/**
 * @file Door.cpp
 * @author Dean Eggenberger
 */

#include "pch.h"
#include "Door.h"

///image of door
const std::wstring doorImageName = L"../images/door.png";


/**
 * Constructor
 * @param game Game this door is a member of
 */
Door::Door(Game *game) : Item(game, doorImageName)
{

}

/**
 * Collision Test function.
 * @param item to test for collisions on
 * @return bool for if anything is colliding with item.
 */
bool Door::CollisionTest(Item* item)
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
    game->OnLevelCompleted();


    return false;

}