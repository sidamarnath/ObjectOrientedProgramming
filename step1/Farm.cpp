/**
 * @file Farm.cpp
 * @author Sid Amarnath
 */

#include "Farm.h"

/**
 * Farm destructor
 */
Farm::~Farm()
{
    // Iterate over all the animals, destroying each one.
    for (auto animal : mInventory)
    {
        delete animal;
    }

    // And clear the list
    mInventory.clear();
}