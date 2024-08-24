/**
 * @file Wall.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef PROJECT1_WALL_H
#define PROJECT1_WALL_H

#include "Item.h"

/**
 * Wall class that inherits from Item class
 */
class Wall : public Item {
private:

    /// wall width
    int mWidth = 0;

    /// wall height
    int mHeight = 0;

    /// The underlying top item image
    std::unique_ptr<wxImage> mTopImage;
    /// The bitmap we can display for the top
    std::unique_ptr<wxBitmap> mTopBitmap;

    /// The underlying center item image
    std::unique_ptr<wxImage> mCenterImage;
    /// The bitmap we can display for the center
    std::unique_ptr<wxBitmap> mCenterBitmap;

    /// The underlying bottom item image
    std::unique_ptr<wxImage> mBottomImage;
    /// The bitmap we can display for the bottom
    std::unique_ptr<wxBitmap> mBottomBitmap;

public:
    /// Default constructor (disabled)
    Wall() = delete;

    /// Copy constructor (disabled)
    Wall(const Wall &) = delete;

    /// Assignment operator
    void operator=(const Wall &) = delete;

    /**
     * Wall added Constructor
     * @param width
     * @param height
     * @param filename
     */
    Wall(Game *game, int width, int height, const std::wstring &filename);

    /**
     * Return width
     * @return mWidth
     */
    double GetWidth() override {return mWidth;}

    /**
     * Return height
     * @return mHeight
     */
    double GetHeight() override {return mHeight;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale) override;

};

#endif //PROJECT1_WALL_H
