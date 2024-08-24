/**
 * @file HiveVisitor.cpp
 * @author Sid Amarnath
 * Visits the hive to infect the population
 */

#include "pch.h"
#include "HiveVisitor.h"
#include "TileHive.h"

/**
 * Visit a TileHive object
 * @param hive hive tile we are visiting
 */
void HiveVisitor::VisitHive(TileHive *hive)
{
    hive->ReleaseTVirus();

}

