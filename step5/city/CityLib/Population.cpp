/**
 * @file Population.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include <sstream>
#include "Population.h"
#include "Tile.h"
#include "City.h"

using namespace std;

/// X offset to draw the people population on a tile in pixels
const int PeopleOffset = -48;

/// X offset to draw the zombie population on a tile in pixels
const int ZombiesOffsetX = 48;

/// Y offset to draw both population values on a tile in pixels
const int PopulationOffsetY = -15;

/// Infected biohazard image
const std::wstring BiohazardImage = L"biohazard.png";


/**
 * Constructor
 * @param tile The tile that owns this object.
 */
Population::Population(Tile* tile) : mTile(tile)
{
    auto city = tile->GetCity();
    auto filename = city->GetImagesDirectory() + L"/" + BiohazardImage;
    mImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mBitmap = make_unique<wxBitmap>(*mImage);
}

/**
 * Reset the population system
 */
void Population::Reset()
{
    mInfected = false;
    mPeople.Set(0);
    mZombies.Set(0);
}

/**
 * Update the time
 * @param elapsed Elapsed time since last called.
 */
void Population::Update(double elapsed)
{
    if(mInfected)
    {
        mInfectionTime += elapsed;

        int newlyInfected = mPeople.Remove(elapsed);
        mZombies.Add(newlyInfected);
    }
}

/**
 * Draw the population information on the tile
 * @param dc Device context to draw on
 */
void Population::Draw(wxDC *dc)
{
    auto city = mTile->GetCity();

    auto x = mTile->GetX();
    auto y = mTile->GetY();

    if(mInfected)
    {
        if (mImage != nullptr)
        {
            int wid = mImage->GetWidth();
            int hit = mImage->GetHeight();

            dc->DrawBitmap(*mBitmap,
                    x - Tile::OffsetLeft,
                    y + Tile::OffsetDown - hit);
        }
    }



    if(city->IsViewPopulation())
    {
        wxFont font(wxSize(0, 16),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
        dc->SetFont(font);

        auto people = mPeople.GetCount();
        if(people > 0)
        {
            std::wstringstream str;
            str << people;

            dc->SetTextForeground(*wxCYAN);
            dc->DrawText(str.str(),  // Text to draw
                    (int)x + PeopleOffset,     // x coordinate for the left size of the text
                    (int)y + PopulationOffsetY);    // y coordinate for the top of the text
        }

        auto zombies = mZombies.GetCount();
        if(zombies > 0)
        {
            std::wstringstream str;
            str << zombies;

            dc->SetTextForeground(*wxRED);
            auto size = dc->GetTextExtent(str.str());
            dc->DrawText(str.str(),  // Text to draw
                    (int)x + ZombiesOffsetX - size.GetWidth(),     // x coordinate for the left size of the text
                    (int)y + PopulationOffsetY);    // y coordinate for the top of the text
        }

    }


}

/**
 * Set the infected status of the population
 * @param infected True if infected
 */
void Population::SetInfected(bool infected)
{
    if(infected == mInfected)
    {
        //  No change
        return;
    }

    mInfected = infected;
    if(mInfected)
    {
        mInfectionTime = 0;      // Start of the infection period
    }
}
