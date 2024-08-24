/**
 * @file TuitionUp.h
 * @author Dean Eggenberger
 *
 *
 */

#ifndef PROJECT1_TUITIONUP_H
#define PROJECT1_TUITIONUP_H
#include "Item.h"

/**
 * TuitionUp class
 */
class TuitionUp : public Item{
private:
    ///value of starting y coordinate
    double mStartHeight = 0;

    /// boolean for if collected or not
    bool collected = false;

    /// Value of text scale
    double mTextScale = 1;
public:
    /// Default constructor (disabled)
    TuitionUp() = delete;

    /// Copy constructor (disabled)
    TuitionUp(const TuitionUp &) = delete;

    /// Assignment operator
    void operator=(const TuitionUp &) = delete;

    ///Added Constructor
    TuitionUp(Game *game, const std::wstring &filename);

    bool CollisionTest(Item* item) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale) override;

    void Update(double elapsed) override;

    void Reset() override;

    void XmlLoad(wxXmlNode* node) override;
};

#endif //PROJECT1_TUITIONUP_H
