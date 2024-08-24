/**
 * @file TileHive.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "TileHive.h"
#include "City.h"
#include "MemberReport.h"

using namespace std;


/// Hive base image
const std::wstring HiveImage = L"hive.png";

/// Hive initial population
const int InitialPopulation = 117;

/// The initial infection rate in people per second
const double InitialInfectionRate = 1;

/// The infection rate acceleration
const double InfectionAcceleration = 4;

/// Rate we distribute zombies in zombies per second
const double DistributionRate = 10;

/** Constructor
* @param city The city this is a member of
*/
TileHive::TileHive(City* city) : Tile(city), mPopulation(this)
{
    SetImage(HiveImage);
    Reset();
}

/**
 * Reset hive to initial condition
 */
void TileHive::Reset()
{
    mPopulation.Reset();
    auto people = mPopulation.GetPeople();
    people->Set(InitialPopulation, InitialInfectionRate, InfectionAcceleration, true);

    auto zombies = mPopulation.GetZombies();
    zombies->Set(0, DistributionRate);
}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileHive::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"hive");

    return itemNode;
}

/**
 * Draw the tile.
 * @param dc Device context to draw on
 */
void TileHive::Draw(wxDC* dc)
{
    Tile::Draw(dc);
    mPopulation.Draw(dc);
}

/**
 * Update the object in time
 * @param elapsed Elapsed time in seconds
 */
void TileHive::Update(double elapsed)
{
    Tile::Update(elapsed);
    mPopulation.Update(elapsed);

    auto people = mPopulation.GetPeople();
    auto zombies = mPopulation.GetZombies();
    if(people->GetCount() == 0 && zombies->GetCount() > 0)
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

/**
 * Generate a report for this  tile.
 * @param report
*/
void TileHive::Report(std::shared_ptr<MemberReport> report)
{
    wstringstream str;
    str << L"Umbrella Corporation Hive";

    report->SetReport(str.str());
}

/**
 * Release the T-Virus, infecting everyone in the lab.
 */
void TileHive::ReleaseTVirus()
{
    mPopulation.SetInfected(true);
}