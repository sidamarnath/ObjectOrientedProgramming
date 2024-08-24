/**
 * @file ResetTileVisitor.h
 * @author Sid Amarnath
 *
 * Resets the city back to the original
 */

#include "TileHive.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileGarden.h"

#ifndef CITY_RESETTILEVISITOR_H
#define CITY_RESETTILEVISITOR_H

/**
 * Resets each tile back to the original
 */
class ResetTileVisitor : public TileVisitor {
private:

public:
    virtual void VisitHive(TileHive *hive) override;
    virtual void VisitLandscape(TileLandscape *landscape) override;
    virtual void VisitBuilding(TileBuilding *building) override;

};

#endif //CITY_RESETTILEVISITOR_H
