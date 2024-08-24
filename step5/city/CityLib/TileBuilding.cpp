/**
 * @file TileBuilding.cpp
 * @author Charles B. Owen
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "TileBuilding.h"
#include "City.h"
#include "MemberReport.h"

/// The initial infection rate in people per second
const double InitialInfectionRate = 1;

/// The infection rate acceleration
const double InfectionAcceleration = 4;

/// Rate we distribute zombies in zombies per second
const double DistributionRate = 20;

using namespace std;


/** Constructor
 * @param city The city this is a member of
 * @param initialPopulation The initial population of this building
*/
TileBuilding::TileBuilding(City *city, int initialPopulation) : Tile(city),
    mInitialPopulation(initialPopulation),
    mPopulation(this)
{
    Reset();
}

/**
 * Reset building tile to initial condition
 */
void TileBuilding::Reset()
{
    mPopulation.Reset();
    auto people = mPopulation.GetPeople();
    people->Set(mInitialPopulation, InitialInfectionRate, InfectionAcceleration, true);

    auto zombies = mPopulation.GetZombies();
    zombies->Set(0, DistributionRate);
}

/**
 * Draw the tile.
 * @param dc Device context to draw on
 */
void TileBuilding::Draw(wxDC* dc)
{
    Tile::Draw(dc);
    mPopulation.Draw(dc);
}

/**
 * Update the object in time
 * @param elapsed Elapsed time in seconds
 */
void TileBuilding::Update(double elapsed)
{
    Tile::Update(elapsed);
    mPopulation.Update(elapsed);

    auto zombies = mPopulation.GetZombies();
    if(zombies->GetCount() > 0)
    {
        // We can distribute zombies
        auto available = zombies->Remove(elapsed);

        // Distribute available zombies to neighboring tiles

        // This line will be replaced:
        int undistributable = available;

        // Add back any undistributable zombies
        zombies->Add(undistributable);
    }

}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileBuilding::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"building");
    itemNode->AddAttribute(L"file", GetFile());
    itemNode->AddAttribute(L"population", wxString::Format(wxT("%i"), mInitialPopulation));

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileBuilding::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
    auto population = node->GetAttribute(L"population", L"10");

    mInitialPopulation = wxAtoi(population);
    Reset();
}



/**
 * Generate a report for this  tile.
 * @param report
*/
void TileBuilding::Report(std::shared_ptr<MemberReport> report)
{
    wstringstream str;
    str << L"Building - " << GetFile();

    report->SetReport(str.str());
}


/**
 * Infect this tile!
 * @return true if newly infected
 */
bool TileBuilding::Infect()
{
    if(!mPopulation.IsInfected())
    {
        mPopulation.SetInfected(true);
        mPopulation.GetZombies()->Add(1);
        return true;
    }

    return false;
}
