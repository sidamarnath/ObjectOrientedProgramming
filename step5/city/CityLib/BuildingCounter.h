/**
 * @file BuildingCounter.h
 * @author Sid Amarnath
 *
 * Counts the number of buildings in the city
 */

#include "TileVisitor.h"

#ifndef CITY_BUILDINGCOUNTER_H
#define CITY_BUILDINGCOUNTER_H

/**
 * Class that counts the number of buildings in the city
 */
class BuildingCounter : public TileVisitor {
private:
    /// Buildings counter
    int mNumBuildings = 0;

public:
    /**
     * Get the number of buildings
     * @return Number of buildings
     */
    int GetNumBuildings() const { return mNumBuildings; }

    /**
     * Visit a TileBuilding object
     * @param building Building we are visiting
     */
    void VisitBuilding(TileBuilding* building)
    {
        mNumBuildings++;
    }

};

#endif //CITY_BUILDINGCOUNTER_H
