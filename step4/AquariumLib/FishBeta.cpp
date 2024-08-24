/**
 * @file FishBeta.cpp
 * @author Sid Amarnath
 * Adds a beta fish to the aquarium
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"

using namespace std;

/// in pixels per second
const double MaxSpeedX = 250;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 200;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium *aquarium) : Fish(aquarium, FishBetaImageName)
{
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    set_m_speed_x(distribution(aquarium->GetRandom()));
    set_m_speed_y(distribution(aquarium->GetRandom()));
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"beta");

    return itemNode;
}





