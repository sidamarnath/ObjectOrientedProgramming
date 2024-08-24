/**
 * @file SpartyGnome.cpp
 * @author Omay Dogan
 */

#include "pch.h"
#include "SpartyGnome.h"
#include "Game.h"
#include "Vector.h"
#include "Collision.h"
#include <cmath>

using namespace std;

///Image of SpartyGnome idle
const wstring SpartyGnomeImageIdle = L"../images/gnome.png";
///Image of SpartyGnome walking left
const wstring SpartyGnomeLeftOne = L"../images/gnome-walk-left-1.png";
///Image of SpartyGnome walking left
const wstring SpartyGnomeLeftTwo = L"../images/gnome-walk-left-2.png";
///Image of SpartyGnome idle walking right
const wstring SpartyGnomeRightOne = L"../images/gnome-walk-right-1.png";
///Image of SpartyGnome idle wlalking right
const wstring SpartyGnomeRightTwo = L"../images/gnome-walk-right-2.png";

/// Acceleration of gravity in virtual pixels per second per second
const float Gravity = 1000;
/// Horizontal speed in virtual pixels per second
const float WalkSpeed = 500;
///Strength of jump
const float JumpStrength = -800;
/// Small value to ensure we do not stay in collision
const double Epsilon = 0.001;


/**
 * Constructor
 * @param game game instance
 */
SpartyGnome::SpartyGnome(Game *game) : Item(game, SpartyGnomeImageIdle)
{
    mGame = game;
    mV = Vector(0, 0);
}

/**
 * Handle updates in time of our gnome
 *
 * This is called before we draw and allows us to
 * move our gnome.
 * @param elapsed Time elapsed since the class call
 */
void SpartyGnome::Update(double elapsed)
{
    // The current position
    Vector p = GetP();

    // Gravity
    // Compute a new velocity with gravity added in.
    Vector newV(mV.X(), mV.Y() + Gravity * elapsed);

    // Update position
    Vector newP = p + newV * elapsed;

    //
    // Try updating the Y location.
    //
    SetLocation(p.X(), newP.Y());

    auto collided = mGame->CollisionTest(this);
    if (collided != nullptr)
    {
        if (newV.Y() > 0)
        {
            // We are falling, stop at the collision point
            newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
            mJumpAvailable = true;
        }
        else
        {
            // We are rising, stop at the collision point
            newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
            mJumpAvailable = false;
        }

        // If we collide, we cancel any velocity
        // in the Y direction
        newV.SetY(0);
    }
    else{
        mJumpAvailable = false;
    }

    //
    // Try updating the X location
    //
    SetLocation(newP.X(), p.Y());

    collided = mGame->CollisionTest(this);
    if (collided != nullptr)
    {
        if (newV.X() > 0)
        {
            // We are moving to the right, stop at the collision point
            newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
        }
        else
        {
            // We are moving to the left, stop at the collision point
            newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
        }


        // If we collide, we cancel any velocity
        // in the X direction
        newV.SetX(0);
    }

    // Update the velocity and position
    mV = newV;
    SetLocation(newP.X(), newP.Y());

    // Check if gnome fell off the map
    if (GetY() > 1200)
    {
        auto game = Item::GetGame();
        game->GnomeDeath();
    }

    // Add the distance walked
    mDistanceWalked += std::abs(newP.X() - p.X());

    if(newP.X() - p.X() > 0.01)
    {
        mIsWalking = true;
        mIsWalkingRight = true;
    }
    else if(newP.X() - p.X() < -0.01)
    {
        mIsWalking = true;
        mIsWalkingRight = false;
    }
    else
    {
        mIsWalking = false;
    }
    if(mDistanceWalked >= 100 && mIsWalking && mJumpAvailable)
    {
        mUsingFirstWalkingImage = !mUsingFirstWalkingImage;
        mDistanceWalked = 0;
    }

}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param scale scale
 */
void SpartyGnome::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale)
{
    if(mIsWalking)
    {
        if(mIsWalkingRight)
        {
            if(mUsingFirstWalkingImage)
            {
                SetBitmap(SpartyGnomeRightOne);
            }
            else
            {
                SetBitmap(SpartyGnomeRightTwo);
            }
        }
        else
        {
            if(mUsingFirstWalkingImage)
            {
                SetBitmap(SpartyGnomeLeftOne);
            }
            else
            {
                SetBitmap(SpartyGnomeLeftTwo);
            }
        }
    }
    else
    {
        SetBitmap(SpartyGnomeImageIdle);
    }
    Item::Draw(graphics, scale);
}

/**
 * Function that resets the SpartyGnome's position and allows it to be redrawn on screen and collectable
 */
void SpartyGnome::Reset()
{
    mIsWalking = false;
    Vector newV(0, 0);
    mV = newV;
    SetBitmap(SpartyGnomeImageIdle);
}

/**
 * Function that initiates jumping
 */
void SpartyGnome::Jump()
{
    if(mJumpAvailable && mAcceptingInput)
    {
        Vector newV(mV.X(), JumpStrength);
        mV = newV;
    }

}

/**
 * Function that is called when player presses the key to move left
 */
void SpartyGnome::MoveLeftDown()
{
    if (!mAcceptingInput) return;
    Vector newV(-WalkSpeed, mV.Y());
    mV = newV;
}

/**
 * Function that is called when player releases the key to move left
 */
void SpartyGnome::MoveLeftUp()
{
    if (!mAcceptingInput) return;
    Vector newV(0, mV.Y());
    mV = newV;
}

/**
 * Function that is called when player presses the key to move right
 */
void SpartyGnome::MoveRightDown()
{
    if (!mAcceptingInput) return;
    Vector newV(WalkSpeed, mV.Y());
    mV = newV;
}

/**
 * Function that is called when player releases the key to move right
 */
void SpartyGnome::MoveRightUp()
{
    if (!mAcceptingInput) return;
    Vector newV(0, mV.Y());
    mV = newV;
}

