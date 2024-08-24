/**
 * @file Farm.h
 * @author Sid Amarnath
 * Class that describes a Farm.
 * This class holds a collection of animals that make
 * up the inventory of a farm.
 */

#ifndef STEP1_FARM_H
#define STEP1_FARM_H

#include <vector>
#include "Cow.h"


/**
 * Class that describes a farm.
 *
 * Holds a collection of animals that make up the farm
 * inventory.
 */

class Farm {
private:
    /// A list with the inventory of all animals on the farm
    std::vector<Animal *> mInventory;

public:
    /** Add an animal to the farm inventory.
    *
    * @param animal An animal to add to the inventory
    */

    void AddAnimal(Animal *animal)
    {
        mInventory.push_back(animal);
    }

    /**
    * Display the farm inventory.
    */
    void DisplayInventory()
    {
        for (auto animal : mInventory)
        {
            animal->DisplayAnimal();
        }
    }

    int NumberOfDefenders()
    {
        int count = 0;
        for (auto animal : mInventory)
        {
            if (animal -> IsDefender()) {
                count ++;
            }
        }
        return count;
    }

    ~Farm();

};

#endif //STEP1_FARM_H
