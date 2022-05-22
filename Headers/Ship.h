#ifndef SHIP_H
#define SHIP_H

#include "BaseObject.h"

class Ship: public BaseObject {
private:
    int shield;

protected:
    const int LENGTH_SIDE_TEXTURE = 76;
    bool isDead = false;

public:
    Ship();
    Ship(SDL_Renderer *renderer);
    void setDead(bool isDead);
    bool getDead() const;
    void setShield(int shield, int maxShield);
    int getShield() const;
    void clean();
};

#endif