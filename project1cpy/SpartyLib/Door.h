/**
 * @file Door.h
 * @author Dean Eggenberger
 *
 *
 */

#ifndef PROJECT1_DOOR_H
#define PROJECT1_DOOR_H

#include "Game.h"
#include "Item.h"

/**
 * Door class
 */
class Door : public Item {
private:

    /// Game object member variable
    Game *mGame;

public:
    /// Default constructor (disabled)
    Door() = delete;

    /// Copy constructor (disabled)
    Door(const Door &) = delete;

    /// Assignment operator
    void operator=(const Door &) = delete;

    Door(Game *game);

    bool CollisionTest(Item* item) override;

};

#endif //PROJECT1_DOOR_H
