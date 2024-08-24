/**
 * @file TileHive.h
 * @author Charles Owen
 *
 * Umbrella corporation hive tile
 */

#ifndef CITY_TILEHIVE_H
#define CITY_TILEHIVE_H

#include "Tile.h"
#include "Population.h"


/**
*  Umbrella corporation hive tile
*/
class TileHive : public Tile
{
private:
    /// The population of the Hive
    Population mPopulation;

public:
    TileHive(City* city);

    ///  Default constructor (disabled)
    TileHive() = delete;

    ///  Copy constructor (disabled)
    TileHive(const TileHive&) = delete;

    virtual wxXmlNode* XmlSave(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Update(double elapsed) override;

    void Draw(wxDC* dc) override;

    /// The supported pruning states
    enum class PruningStates { Pruned, Overgrown1, Overgrown2, Overgrown3, Overgrown4 };

    void ReleaseTVirus();

    void Reset();

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitHive(this); }

};

#endif //CITY_TILEHIVE_H
