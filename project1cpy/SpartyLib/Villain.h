/**
 * @file Villain.h
 * @author Dean Eggenberger
 *
 *
 */

#ifndef PROJECT1_VILLAIN_H
#define PROJECT1_VILLAIN_H

#include "Item.h"
#include "Vector.h"

/**
 * Villain item class
 */
class Villain : public Item {
private:
    ///boolean value for if villain is going up
    bool mGoingUp = true;

    ///starting y coordinate for villain
    double mStartHeight = 0;
public:

    /**
     * Villain added Constructor
     * @param game Game this door is a member of
     * @param filename filename
     */
    Villain(Game *game, const std::wstring &filename);

    /// Default constructor (disabled)
    Villain() = delete;

    /// Copy constructor (disabled)
    Villain(const Villain &) = delete;

    /// Assignment operator
    void operator=(const Villain &) = delete;

    void XmlLoad(wxXmlNode *node) override;

    void Update(double elapsed) override;

    bool CollisionTest(Item *item) override;
};

#endif //PROJECT1_VILLAIN_H
