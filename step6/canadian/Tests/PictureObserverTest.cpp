/**
 * @file PictureObserverTest.cpp
 * @author Sid Amarnath
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <PictureObserver.h>
#include <PictureObserverMock.h>
#include <Picture.h>

TEST(PictureObserverTest, Construct)
{
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, GetPicture)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And get it for the observer:
    observer.SetPicture(picture);

    //picture->UpdateObservers();

    ASSERT_EQ(observer.GetPicture(), picture);
}

TEST(PictureObserverTest, TwoObservers)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer1;
    PictureObserverMock observer2;

    // And set it for the observer:
    observer1.SetPicture(picture);
    observer2.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer1.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, DestroyObserver)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();
    PictureObserverMock observer1;
    observer1.SetPicture(picture);
    {
        PictureObserverMock observer2;

        // And set it for the observer:
        observer2.SetPicture(picture);
    }
    picture->UpdateObservers();
    ASSERT_TRUE(observer1.mUpdated);

}
