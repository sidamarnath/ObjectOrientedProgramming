/**
 * @file FishAngler.h
 * @author Sid Amarnath
 *
 * Adds an angler fish to the aquarium
 */

#include "Item.h"
#include "Fish.h"

#ifndef AQUARIUM_FISHANGLER_H
#define AQUARIUM_FISHANGLER_H

class FishAngler : public Fish {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;
    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:
    FishAngler() = delete;

    /// Copy constructor (disabled)
    FishAngler(const FishAngler &) = delete;

    /// Assignment operator
    void operator=(const FishAngler &) = delete;

    FishAngler(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //AQUARIUM_FISHANGLER_H
