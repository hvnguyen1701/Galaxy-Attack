#ifndef BULLET_H
#define BULLET_H

#include "BaseObject.h"

class Bullet: public BaseObject {
    const int SPEED = 10;
    bool isActive;

public:
    Bullet(SDL_Renderer *renderer);
    void setActivation(bool isActive);
    bool getActivation() const;
    void move(bool isPlayer, int screenHeight);
};

#endif