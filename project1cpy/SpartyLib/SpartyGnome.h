/**
 * @file SpartyGnome.h
 * @author Omay Dogan
 *
 *
 */

#ifndef PROJECT1_SPARTYGNOME_H
#define PROJECT1_SPARTYGNOME_H

#include "Item.h"
#include "Vector.h"

class Game;

/**
 * Sparty Gnome Item class that the player controls
 */
class SpartyGnome : public Item {
private:

    /// Vector mV
    Vector mV;

    /// Game instance
    Game* mGame;

    /// Check if gnome is on a platform
    bool mJumpAvailable = false;

    /// If this is true, we are using the first image for walking, if false we use second one
    bool mUsingFirstWalkingImage = true;

    /// Measure distance walked to switch animation
    double mDistanceWalked = 0;

    /// Keep track of weather gnome is walking or not
    bool mIsWalking = false;

    /// Keep track of walking direction
    bool mIsWalkingRight = false;

    /// Keeps track of input acceptance
    bool mAcceptingInput = true;
public:
    /// Default constructor (disabled)
    SpartyGnome() = delete;

    /// Copy constructor (disabled)
    SpartyGnome(const SpartyGnome &) = delete;

    /// Assignment operator
    void operator=(const SpartyGnome &) = delete;

    /// Constructor that accepts game
    SpartyGnome(Game* game);

    void Update(double elapsed) override;

    /**
     * Getter for position
     * @return x and y values
     */
    Vector GetP() {return {GetX(), GetY()}; };

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale) override;

    void Jump();
    void MoveLeftDown();
    void MoveLeftUp();
    void MoveRightDown();
    void MoveRightUp();

    /**
     * Setter for Accepting input
     * @param accepting input.
     */
    void SetAcceptingInput(bool accepting) {mAcceptingInput = accepting;}

    void Reset() override;
};

#endif //PROJECT1_SPARTYGNOME_H
