/**
 * @file Fish.cpp
 * @author Sid Amarnath
 * Base Class for all fish
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"


using namespace std;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 20;


/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 10;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
        Item(aquarium, filename)
{

    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = distribution(aquarium->GetRandom());

}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);

    if (mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - 10 - (GetWidth() / 2))
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }

    if (mSpeedX < 0 && GetX() <= (GetWidth() / 2) + 10)
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }

    if (mSpeedY > 0 && GetY() >= GetAquarium()->GetHeight() - 10 - (GetHeight() / 2))
    {
        mSpeedY = -mSpeedY;
    }

    if (mSpeedY < 0 && GetY() <= (GetHeight() / 2) + 10)
    {
        mSpeedY = -mSpeedY;
    }

}

void Fish::set_m_speed_x(double m_speed_x)
{
    mSpeedX = m_speed_x;
}

void Fish::set_m_speed_y(double m_speed_y)
{
    mSpeedY = m_speed_y;
}


