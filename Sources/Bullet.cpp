#include "../Headers/Bullet.h"

using std::string;

Bullet::Bullet(SDL_Renderer *renderer): BaseObject(renderer) {
    dst = {-1, -1, 15, 50};
    isActive = false;
}

void Bullet::setActivation(bool isActive) {
    this->isActive = isActive;
}

bool Bullet::getActivation() const {
    return isActive;
}

void Bullet::move(bool isPlayer, int screenHeight) {
    if (isActive) {
        if (isPlayer) {
            dst.y -= SPEED;
            if (dst.y + dst.h < 0) isActive = false;
        }
        else {
            dst.y += SPEED;
            if (dst.y > screenHeight) isActive = false;
        }
    }
}