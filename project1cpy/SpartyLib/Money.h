/**
 * @file Money.h
 * @author Omay Dogan
 *
 *
 */

#ifndef PROJECT1_MONEY_H
#define PROJECT1_MONEY_H

#include "Item.h"

/**
 * Money item class
 */
class Money : public Item{
private:
    /// is this boolean for if collected by the player
    bool mCollected = false;

    ///starting y value for money
    double mStartHeight = 0;

    ///amount the money is worth
    int mAmount;
public:
    /// Default constructor (disabled)
    Money() = delete;

    /// Copy constructor (disabled)
    Money(const Money &) = delete;

    /// Assignment operator
    void operator=(const Money &) = delete;

    /**
     * Money added Constructor
     * @param game game this item is a member of
     * @param filename filename
     * @param amount amount gained when collected
     */
    Money(Game *game, const std::wstring &filename, int amount);

    bool CollisionTest(Item *item) override;

    void Update(double elapsed) override;

    /// Function to load the items from an XML file
    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale) override;

    void Reset() override;
};

#endif //PROJECT1_MONEY_H
