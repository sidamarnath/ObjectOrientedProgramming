/**
 * @file TileLandscape.cpp
 *
 * @author Charles B. Owen
 */

#include "pch.h"
#include "TileLandscape.h"
#include "City.h"
#include "MemberReport.h"

/// Rate we distribute zombies in zombies per second
const double DistributionRate = 40;

using namespace std;


/** Constructor
* @param city The city this is a member of
*/
TileLandscape::TileLandscape(City *city) : Tile(city), mPopulation(this)
{
    Reset();
}

/**
 * Reset landscape tile to initial condition
 */
void TileLandscape::Reset()
{
    mPopulation.Reset();
    auto people = mPopulation.GetPeople();
    people->Set(0);

    auto zombies = mPopulation.GetZombies();
    zombies->Set(0, DistributionRate);
}


/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileLandscape::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"landscape");
    itemNode->AddAttribute(L"file", GetFile());

    return itemNode;
}

/**
 * Draw the tile.
 * @param dc Device context to draw on
 */
void TileLandscape::Draw(wxDC* dc)
{
    Tile::Draw(dc);
    mPopulation.Draw(dc);
}

/**
 * Update the object in time
 * @param elapsed Elapsed time in seconds
 */
void TileLandscape::Update(double elapsed)
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

/**
* Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileLandscape::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}

/**
 * Generate a report for this landscape tile.
 * @param report 
*/
void TileLandscape::Report(std::shared_ptr<MemberReport> report)
{
    report->SetReport(L"Landscape");
}

/**
 * Receive zombies!
 * @param cnt Number of zombies to receive
 */
void TileLandscape::ReceiveZombies(int cnt)
{
    auto zombies = mPopulation.GetZombies();
    zombies->Add(cnt);
}

/**
 * Infect this tile!
 */
void TileLandscape::Infect()
{
    mPopulation.SetInfected(true);
}
