/**
 * @file PictureObserverMock.h
 * @author Sid Amarnath
 *
 * Mock class for our picture observer
 */
#include "PictureObserver.h"
#ifndef CANADIANEXPERIENCE_PICTUREOBSERVERMOCK_H
#define CANADIANEXPERIENCE_PICTUREOBSERVERMOCK_H

/// Mock class for our picture observer
class PictureObserverMock : public PictureObserver{
private:

public:
    /**
     * Constructor
     */
    PictureObserverMock() : PictureObserver() {}

    /**
     * Sets picture for actor
     * @returns true to update the observer
     */
    virtual void UpdateObserver() override {mUpdated = true;}

    /**
     * bool to check wither to update or not
     */
    bool mUpdated = false;

};

#endif //CANADIANEXPERIENCE_PICTUREOBSERVERMOCK_H
