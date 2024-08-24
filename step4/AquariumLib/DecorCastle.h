/**
 * @file DecorCastle.h
 * @author Sid Amarnath
 *
 * Adding a castle decor to the aquarium
 */

#include "Item.h"

#ifndef AQUARIUM_DECORCASTLE_H
#define AQUARIUM_DECORCASTLE_H

class DecorCastle: public Item {
private:

public:
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle &) = delete;

    /// Assignment operator
    void operator=(const DecorCastle &) = delete;

    DecorCastle(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //AQUARIUM_DECORCASTLE_H
