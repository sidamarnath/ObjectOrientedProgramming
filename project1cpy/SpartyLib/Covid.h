/**
 * @file Covid.h
 * @author Dean Eggenberger
 *
 *
 */

#ifndef PROJECT1_COVID_H
#define PROJECT1_COVID_H

#include "Item.h"
#include "Vector.h"

/**
 * Covid item class
 */
class Covid : public Item{
private:

    /// boolean for if item is moving left.
    bool mGoingLeft = true;

    /// Starting X coordinate.
    double mStartX = 0;
public:

    /**
     * Covid added Constructor
     * @param game game this item is member of
     * @param filename filename
     */
    Covid(Game *game, const std::wstring &filename);

    /// Default constructor (disabled)
    Covid() = delete;

    /// Copy constructor (disabled)
    Covid(const Covid &) = delete;

    /// Assignment operator
    void operator=(const Covid &) = delete;

    void XmlLoad(wxXmlNode *node) override;

    void Update(double elapsed) override;

    bool CollisionTest(Item *item) override;



};

#endif //PROJECT1_COVID_H
