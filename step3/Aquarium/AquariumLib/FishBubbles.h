/**
 * @file FishBubbles.h
 * @author Sid Amarnath
 *
 *
 */

#include "Item.h"

#ifndef AQUARIUM_FISHBUBBLES_H
#define AQUARIUM_FISHBUBBLES_H

class FishBubbles : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;


public:
    FishBubbles() = delete;

    /// Copy constructor (disabled)
    FishBubbles(const FishBubbles &) = delete;

    /// Assignment operator
    void operator=(const FishBubbles &) = delete;

    FishBubbles(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

};

#endif //AQUARIUM_FISHBUBBLES_H
