/**
 * @file ResetTileVisitor.cpp
 * @author Sid Amarnath
 * Resets the city back to the original
 */
#include "pch.h"
#include "ResetTileVisitor.h"

/**
 * Reset a TileHive object
 * @param hive hive tile we are resetting
 */
void ResetTileVisitor::VisitHive(TileHive *hive)
{
    hive->Reset();

}

/**
 * Reset a TileLandscape object
 * @param landscape landscape tile we are resetting
 */
void ResetTileVisitor::VisitLandscape(TileLandscape *landscape)
{
    landscape->Reset();

}

/**
 * Reset a TileBuilding object
 * @param building building tile we are resetting
 */
void ResetTileVisitor::VisitBuilding(TileBuilding *building)
{
    building->Reset();

}

