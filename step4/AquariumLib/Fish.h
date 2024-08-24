/**
 * @file Fish.h
 * @author Sid Amarnath
 *
 * Base class for all fish
 */

#include "Item.h"
#include "Aquarium.h"
#include <random>

#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H


class Fish : public Item {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

    /// Random number generator
    std::mt19937 mRandom;


protected:
    Fish(Aquarium *aquarium, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

    void Update(double elapsed);

    void set_m_speed_x(double m_speed_x);

    void set_m_speed_y(double m_speed_y);


};

#endif //AQUARIUM_FISH_H
