/**
 * @file PictureFactory.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;
class HaroldFactory;
class HenryFactory;

/// Factory for the picture
class PictureFactory {
private:

public:
    /**
 * Creates the picture
 * @param imagesDir image directory
 * @returns the final picture
 */
    std::shared_ptr<Picture> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
