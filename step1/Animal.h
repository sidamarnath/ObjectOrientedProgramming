/**
 * @file Animal.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef STEP1_ANIMAL_H
#define STEP1_ANIMAL_H

class Animal {
private:


public:
    virtual ~Animal();

    /** Display an animal. */
    virtual void DisplayAnimal() {}
    /** Display a defender. */
    virtual bool IsDefender() {}

};

#endif //STEP1_ANIMAL_H
