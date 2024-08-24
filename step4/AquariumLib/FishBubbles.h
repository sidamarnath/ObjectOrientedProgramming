/**
 * @file FishBubbles.h
 * @author Sid Amarnath
 *
 * Adds a bubble fish to the aquarium
 */

#include "Item.h"
#include "Fish.h"

#ifndef AQUARIUM_FISHBUBBLES_H
#define AQUARIUM_FISHBUBBLES_H

class FishBubbles : public Fish {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;
    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:
    FishBubbles() = delete;

    /// Copy constructor (disabled)
    FishBubbles(const FishBubbles &) = delete;

    /// Assignment operator
    void operator=(const FishBubbles &) = delete;

    FishBubbles(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //AQUARIUM_FISHBUBBLES_H
