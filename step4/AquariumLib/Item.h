/**
 * @file Item.h
 * @author Sid Amarnath
 *
 * Base class for any item in our aquarium
 */

#include <memory>

#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

class Aquarium;

class Item {
private:
    Aquarium   *mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    bool mMirror = false;   ///< True mirrors the item image


protected:
    Item(Aquarium *aquarium, const std::wstring &filename);


public:
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;


    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    void Draw(wxDC *dc);

    bool HitTest(int x, int y);

    double DistanceTo(std::shared_ptr<Item> item);

    virtual wxXmlNode *XmlSave(wxXmlNode *node);

    virtual void XmlLoad(wxXmlNode *node);

    virtual void Update(double elapsed) {}

    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium *GetAquarium() { return mAquarium;  }

    void SetMirror(bool m);

    int GetHeight() const { return mItemImage->GetHeight();}

    int GetWidth() const { return mItemImage->GetWidth();}

};

#endif //AQUARIUM_ITEM_H
