/**
 * @file Item.h
 *
 * @author Kathryn Nagy
 *
 * Abstract class representing all items that are within the current game window.
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <string>
#include <wx/image.h>

class Game;

/**
 * Item class
 */
class Item {
private:
    double mX; ///< X location of the item
    double mY; ///< Y location of the item

    /// The game this item is contained in
    Game *mGame;

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;
    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

    /// boolean denoting if rendered
    bool mRender = true;
protected:
    /// Virtual Constructor
    Item(Game* game, const std::wstring &filename);
public:
    virtual ~Item();
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /**
     * Load item
     * @param node node for item
     */
    virtual void XmlLoad(wxXmlNode *node);


    /**
     * Getter to return X pos of this item
     * @return mX image location x
     */
    virtual double GetX() {return mX;}
    /**
     * Getter to return Y pos of this item
     * @return mY image location y
     */
    virtual double GetY() {return mY;}

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Set whether the item should be rendered
     * @param render for mRender
     */
     virtual void SetRender(bool render) {mRender = render;}

    /**
     * Update the item
     * @param elapsed time since last frame
     */
    virtual void Update(double elapsed) {};


    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale);

    /**
     * Get the bitmap to draw this item
     * @return mItemBitmap for drawing
     */
    virtual wxBitmap GetBitmap() {return *mItemBitmap;}

    /**
     * Change item image
     * @param filename image location
     */
    virtual void SetBitmap(const std::wstring &filename);

    /**
     * Return width of mItemBitmap
     * @return mItemBitmap image
     */
    virtual double GetWidth() {return mItemBitmap->GetWidth();}

    /**
     * Return height of mItemBitmap
     * @return mItemBitmap image
     */
    virtual double GetHeight() {return mItemBitmap->GetHeight();}

    /**
     * Getter for the game
     * @return Game
     */
    Game* GetGame() {return mGame; }

    virtual bool CollisionTest(Item *item);

    /**
    * Reset function.
    */
    virtual void Reset() {}; ///< Function to reset an item that is overriden in classes that need it

    /// Returns mTuitionMultiplier of mGame
    float GameTuitionMultiplier();
};


#endif //PROJECT1_ITEM_H
