/**
 * @file Aquarium.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>

class Aquarium {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use


public:
    void OnDraw(wxDC* dc);

    /**
    * Aquarium Constructor
    */
    Aquarium();


};

#endif //AQUARIUM_AQUARIUM_H
