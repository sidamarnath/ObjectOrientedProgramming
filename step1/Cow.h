/**
 * @file Cow.h
 * @author Sid Amarnath
 * Class that describes the inventory of cows in the farm
 *
 */

#ifndef STEP1_COW_H
#define STEP1_COW_H
#include <string>
#include <iostream>
#include "Animal.h"

/**
* Class that describes the cows in the farm
*
* Holds a collection of the inventory of the cows in the farm.
*/

class Cow : public Animal {
private:
    /// The types of cow we can have on our farm
    enum class Type {Bull, BeefCow, MilkCow};

    /// The cow's name
    std::string mName;

    /// The type of cow: Bull, BeefCow, or MilkCow
    Type mType =Type::MilkCow;

    /// The milk production for a cow in gallons per day
    double mMilkProduction = 0;

public:
    void ObtainCowInformation();
    void DisplayAnimal();

};

#endif //STEP1_COW_H
