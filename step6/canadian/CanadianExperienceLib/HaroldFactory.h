/**
 * @file HaroldFactory.h
 * @author Sid Amarnath
 *
 * Factory class that builds the Harold character
 */

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

class Actor;

/**
 * Creating the actor Henry
 */
class HaroldFactory {
private:
    /// Position as a point
    wxPoint mPosition;

public:
    /**
     * Creates actor Harold
     * @param imagesDir Images directory
     * @returns pointer to an actor object
     */
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
