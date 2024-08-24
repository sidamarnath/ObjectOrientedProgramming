/**
 * @file FishBeta.h
 * @author Sid Amarnath
 *
 * Adds a beta fish to the aquarium
 */

#include "Item.h"
#include "Fish.h"

#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H



class FishBeta : public Fish {
private:


public:
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;

    FishBeta(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;


};

#endif //AQUARIUM_FISHBETA_H
