/**
 * @file Collision.h
 * @author Omay Dogan
 *
 *
 */

#ifndef PROJECT1_COLLISION_H
#define PROJECT1_COLLISION_H

/**
 * Collision class
 */
class Collision {
private:
    /// X location of the collided item
    double mX = 0;

    /// Y location of the collided item
    double mY = 0;

    /// Width of collided item
    double mWidth = 0;

    /// Height of collided item
    double mHeight = 0;
public:
    /// Default constructor;
    Collision() = default;

    /// Copy constructor (disabled)
    Collision(const Collision &) = default;

    /// Destructor
    virtual ~Collision() = default;

    /**
     * Getter for the x coordinate
     * @return double mX
     */
    virtual double GetX() {return mX;}

    /**
     * Getter for the y coordinate
     * @return double mY
     */
    virtual double GetY() {return mY;}

    /**
     * Setter for the location
     * @param x double x
     * @param y double y
     */
    virtual void SetLocation(double x, double y) {mX = x; mY = y;}

    /**
     * Return width of collided item
     * @return mWidth (double)
     */
    virtual double GetWidth() {return mWidth;}

    /**
     * Return height of collided item
     * @return mHeight as a double
     */
    virtual double GetHeight() {return mHeight;}

    /**
     * Set width info of collision item
     * @param width as a double
     */
    virtual void SetWidth(double width) {mWidth = width;}

    /**
     * Set height info of collision item
     * @param height double height
     */
    virtual void SetHeight(double height) {mHeight = height;}
};

#endif //PROJECT1_COLLISION_H
