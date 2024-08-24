/**
 * @file Aquarium.cpp
 * @author Sid Amarnath
 */
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishBubbles.h"
#include "FishAngler.h"
#include "Item.h"

#include <algorithm>

using namespace std;


Aquarium::Aquarium()
{
    mBackground = make_unique<wxBitmap>(L"images/background1.png", wxBITMAP_TYPE_ANY);

}

/**
 * Draw the aquarium
 * @param dc The device context to draw on
 */
void Aquarium::OnDraw(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));
    dc->DrawText(L"Under the Sea!", 10, 10);

    for (auto item : mItems)
    {
        item->Draw(dc);
    }
}

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
 * Add an item to the aquarium
 * @param item New item to add
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
    item->SetLocation(InitialX, InitialY);
    for (auto i = mItems.begin(); i != mItems.end();  i++)
    {
        if ((*i)->DistanceTo(item) <= 1)
        {
            item->SetLocation((*i)->GetX() + 10, (*i)->GetY() + 10);
            for (auto j = mItems.begin(); j != mItems.end();  j++)
            {
                if ((*j)->DistanceTo(item) <= 1)
                {
                    item->SetLocation((*j)->GetX() + 10, (*j)->GetY() + 10);
                }
            }
        }
    }
    mItems.push_back(item);

}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

void Aquarium::MoveToFront(shared_ptr<Item>(item))
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
        mItems.push_back(item);
    }
}














