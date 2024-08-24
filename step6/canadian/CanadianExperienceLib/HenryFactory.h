/**
 * @file HenryFactory.h
 * @author Sid Amarnath
 *
 * Factory class that builds the Henry character
 */

#ifndef CANADIANEXPERIENCE_HENRYFACTORY_H
#define CANADIANEXPERIENCE_HENRYFACTORY_H

class Actor;

/**
 * Creating the actor Henry.
 */
class HenryFactory {
private:

public:
    /**
     * Creates actor Henry
     * @param imagesDir Images directory
     * @returns pointer to an actor object
     */
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_HENRYFACTORY_H
