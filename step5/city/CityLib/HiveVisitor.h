/**
 * @file HiveVisitor.h
 * @author Sid Amarnath
 *
 * Visits the hive to infect the population
 */

#include "TileHive.h"
#include "TileVisitor.h"


#ifndef CITY_HIVEVISITOR_H
#define CITY_HIVEVISITOR_H


/**
 * Visitor that visits the hive.
*/
class HiveVisitor : public TileVisitor {
private:

public:
    /**
     * Visit the hive
     * @return void
     */
    virtual void VisitHive(TileHive *hive) override;


};

#endif //CITY_HIVEVISITOR_H
