/**
 * @file DrawableMock.h
 * @author Sid Amarnath
 *
 * Mock class for Drawable
 */

#ifndef CANADIANEXPERIENCE_DRAWABLEMOCK_H
#define CANADIANEXPERIENCE_DRAWABLEMOCK_H

#include "Drawable.h"

/**
 * Mock class for testing Drawable
 */
class DrawableMock : public Drawable {
private:

public:
    /**
     * Constructor
    * @param name Name of the drawable
     */
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    /**
     * Draws the drawable
    * @param graphics shared ptr to wxGraphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}

    /**
     * Tests to see if we have clicked on anything
    * @param pos Position of a point
     * @returns false
     */
    virtual bool HitTest(wxPoint pos) override { return false; }

};

#endif //CANADIANEXPERIENCE_DRAWABLEMOCK_H
