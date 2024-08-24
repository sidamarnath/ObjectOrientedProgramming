/**
* @file TileBuilding.h
*
* @author Charles B. Owen
*
*  Class that implements a Building tile
*/

#pragma once

#include "Tile.h"
#include "Population.h"

/**
*  A Building tile
*/
class TileBuilding : public Tile
{
private:
    /// Building initial population
    int mInitialPopulation;

    /// Building population management
    Population mPopulation;

public:
    TileBuilding(City *city, int initialPopulation=10);

    ///  Default constructor (disabled)
    TileBuilding() = delete;

    ///  Copy constructor (disabled)
    TileBuilding(const TileBuilding &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Reset();

    void Update(double elapsed) override;

    void Draw(wxDC* dc) override;

    bool Infect();

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitBuilding(this); }
};

