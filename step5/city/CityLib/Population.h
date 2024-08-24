/**
 * @file Population.h
 * @author Charles Owen
 *
 * Represents the population of a city tile.
 */

#ifndef CITY_POPULATION_H
#define CITY_POPULATION_H

#include "PopulationSegment.h"

class Tile;

/**
 * Represents the population of a city tile.
 */
class Population {
private:
    /// The owning tile
    Tile *mTile;

    /// The collection of people
    PopulationSegment mPeople;

    /// The collection of zombies
    PopulationSegment mZombies;

    /// The time since object was created in seconds
    double mInfectionTime = 0;

    /// Is this population infected?
    bool mInfected = false;

    /// The biohazard image
    std::unique_ptr<wxImage> mImage;

    /// The bitmap for the biohazard image
    std::unique_ptr<wxBitmap> mBitmap;

public:
    Population(Tile *tile);

    void Update(double elapsed);

    void Draw(wxDC*);

    void SetInfected(bool infected);

    /**
     * Get the infected status of the population
     * @return true if infected
     */
    bool IsInfected() {return mInfected;}

    /**
     * Get the population of people
     * @return People population object
     */
    auto GetPeople() {return &mPeople;}

    /**
     * Get the population of zombies
     * @return Zombies population object
     */
    auto GetZombies() {return &mZombies;}

    void Reset();
};

#endif //CITY_POPULATION_H
