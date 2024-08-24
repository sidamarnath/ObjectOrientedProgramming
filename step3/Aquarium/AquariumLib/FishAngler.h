/**
 * @file FishAngler.h
 * @author Sid Amarnath
 *
 *
 */

#include "Item.h"

#ifndef AQUARIUM_FISHANGLER_H
#define AQUARIUM_FISHANGLER_H

class FishAngler : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;


public:
    FishAngler() = delete;

    /// Copy constructor (disabled)
    FishAngler(const FishAngler &) = delete;

    /// Assignment operator
    void operator=(const FishAngler &) = delete;

    FishAngler(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

};

#endif //AQUARIUM_FISHANGLER_H
