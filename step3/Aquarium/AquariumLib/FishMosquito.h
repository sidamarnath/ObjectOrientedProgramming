/**
 * @file FishMosquito.h
 * @author Sid Amarnath
 *
 *
 */

#include "Item.h"

#ifndef AQUARIUM_FISHMOSQUITO_H
#define AQUARIUM_FISHMOSQUITO_H

class FishMosquito : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    FishMosquito() = delete;

    /// Copy constructor (disabled)
    FishMosquito(const FishMosquito &) = delete;

    /// Assignment operator
    void operator=(const FishMosquito &) = delete;

    FishMosquito(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

};

#endif //AQUARIUM_FISHMOSQUITO_H
