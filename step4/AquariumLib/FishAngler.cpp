/**
 * @file FishAngler.cpp
 * @author Sid Amarnath
 * Adds an angler fish to the aquarium
 */

#include "pch.h"
#include "FishAngler.h"
#include "Aquarium.h"

using namespace std;

/// in pixels per second
const double MaxSpeedX = 150;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 100;

/// Fish filename
const wstring FishAnglerImageName = L"images/angler.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishAngler::FishAngler(Aquarium *aquarium) : Fish(aquarium, FishAnglerImageName)
{
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    set_m_speed_x(distribution(aquarium->GetRandom()));
    set_m_speed_y(distribution(aquarium->GetRandom()));


}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return item node
 */
wxXmlNode* FishAngler::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"angler");

    return itemNode;
}






