/**
 * @file Ant.h
 * @author Sid Amarnath
 *
 * Class that describes the inventory of ants in the farm
 */

#ifndef STEP1_ANT_H
#define STEP1_ANT_H

#include <string>
#include <iostream>
#include "Animal.h"

/**
* Class that describes the ants in the farm
*
* Holds a collection of the inventory of the ants in the farm.
*/

class Ant : public Animal{
private:
    /// The types of ant we can have on our farm
    enum class Type {Worker, Soldier, Drone, Queen};

    /// The ant's code
    std::string mCode;

    /// The type of ant: Worker, Soldier, Drone, or Queen
    Type mType =Type::Worker;

    /// The radiation level of this ant (millisieverts per hour)
    double mRadiationLevel = 0;

public:
    void ObtainAntInformation();
    void DisplayAnimal();

    bool IsDefender();
};

#endif //STEP1_ANT_H
