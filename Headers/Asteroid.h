#ifndef ASTEROID_H
#define ASTEROID_H

#include "BaseObject.h"

class Asteroid: public BaseObject { 
    const int X_SPEED = 1;
    const int Y_SPEED = 2;
    const int NUMBER_ROWS_IMAGE = 4;
    const int NUMBER_COLUMNS_IMAGE = 4;
    const int DISTANCE_BETWEEN_2_IMAGES = 4;
    
    int iRow = 0, jColumn = 0, count = 0;
    bool isActive, isFromLeft;

public:
    Asteroid(SDL_Renderer *renderer, int screenWidth, int screenHeight);
    void setImage(SDL_Texture *image);
    void setActivation(bool isActive);
    bool getActivation() const;
    void move(int screenWidth, int screenHeight);
    void animate();
};

#endif