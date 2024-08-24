/**
 * @file Item.cpp
 * @author Sid Amarnath
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 */
Item::Item(Aquarium *aquarium) : mAquarium(aquarium)
{

}

/**
 * Destructor
 */
Item::~Item()
{

}
