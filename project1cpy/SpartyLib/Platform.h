/**
 * @file Platform.h
 * @author Omay
 *
 *
 */

#ifndef PROJECT1_PLATFORM_H
#define PROJECT1_PLATFORM_H

#include "Item.h"
/**
 * Platform class that inherits from Item class
 */
class Platform : public Item {
private:
    ///platform width value
    int mWidth = 0;
    ///platform height value
    int mHeight = 0;

    /// The underlying left item image
    std::unique_ptr<wxImage> mLeftImage;
    /// The bitmap we can display for the left
    std::unique_ptr<wxBitmap> mLeftBitmap;

    /// The underlying center item image
    std::unique_ptr<wxImage> mCenterImage;
    /// The bitmap we can display for the center
    std::unique_ptr<wxBitmap> mCenterBitmap;

    /// The underlying right item image
    std::unique_ptr<wxImage> mRightImage;
    /// The bitmap we can display for the right
    std::unique_ptr<wxBitmap> mRightBitmap;
public:
    /// Default constructor (disabled)
    Platform() = delete;

    /// Copy constructor (disabled)
    Platform(const Platform &) = delete;

    /// Assignment operator
    void operator=(const Platform &) = delete;

    Platform(Game *game, int width, int height, const std::wstring &leftFilename, const std::wstring &centerFilename, const std::wstring &rightFilename);

    /**
     * Get width
    * @return mWidth width
    */
    double GetWidth() override {return mWidth;}

    /**
     * Get height
    * @return mHeight Height
    */
    double GetHeight() override {return mHeight;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale) override;
};

#endif //PROJECT1_PLATFORM_H
