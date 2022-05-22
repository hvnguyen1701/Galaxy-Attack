#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Ship.h"

class EnemyShip: public Ship {
    const int SPEED = 2;
    bool isActive, isMovingLeft;

public:
    EnemyShip(SDL_Renderer *renderer, int screenWidth);
    void setActivation(bool isActive);
    bool getActivation() const;
    void move(int screenWidth, int screenHeight);
};

#endif