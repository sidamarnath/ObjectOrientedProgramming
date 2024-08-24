/**
 * @file Aquarium.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>


class Item;

class Aquarium {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use
    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;


public:
    /**
    * Aquarium Constructor
    */
    Aquarium();

    void OnDraw(wxDC* dc);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void MoveToFront(std::shared_ptr<Item>(item));









};

#endif //AQUARIUM_AQUARIUM_H
