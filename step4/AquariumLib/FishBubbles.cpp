/**
 * @file FishBubbles.cpp
 * @author Sid Amarnath
 * Adds a bubble fish to the aquarium
 */

#include "pch.h"
#include "FishBubbles.h"
#include "Aquarium.h"

using namespace std;

/// in pixels per second
const double MaxSpeedX = 100;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 50;

/// Fish filename
const wstring FishBubblesImageName = L"images/bubbles.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBubbles::FishBubbles(Aquarium *aquarium) : Fish(aquarium, FishBubblesImageName)
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
wxXmlNode* FishBubbles::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"bubbles");

    return itemNode;
}



