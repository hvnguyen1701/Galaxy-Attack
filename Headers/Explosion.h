#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "BaseObject.h"

class Explosion: public BaseObject {
    const int DISTANCE_BETWEEN_2_IMAGES = 2;
    
    int numberRowsImage, numberColumnsImage;
    int count = 0, iRow, jColumn;
    bool isActive;

public:
    Explosion();
    Explosion(SDL_Renderer *renderer);
    void setImage(SDL_Texture *image, int numberRowsImage, int numberColumnsImage);
    void setActivation(bool isActive);
    bool getActivation() const;
    void animate();
};

#endif