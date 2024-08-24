/**
* @file TileLandscape.h
*
* @author Charles B. Owen
*
*  Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"
#include "Population.h"

/**
*  A Landscape tile
*/
class TileLandscape : public Tile
{
private:
    /// The population of the Landscape
    Population mPopulation;

public:
    TileLandscape(City *city);

    ///  Default constructor (disabled)
    TileLandscape() = delete;

    ///  Copy constructor (disabled)
    TileLandscape(const TileLandscape &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;
    void Reset();

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Draw(wxDC* dc) override;

    void ReceiveZombies(int cnt);
    void Infect();

    void Update(double elapsed) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitLandscape(this); }
};

