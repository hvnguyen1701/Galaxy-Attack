#include "../Headers/Ship.h"

using std::string;

Ship::Ship() {
    dst = {-1, -1, LENGTH_SIDE_TEXTURE, LENGTH_SIDE_TEXTURE};
}

Ship::Ship(SDL_Renderer *renderer): BaseObject(renderer) {}

void Ship::setDead(bool isDead) {
    this->isDead = isDead;
}

bool Ship::getDead() const {
    return isDead;
}

void Ship::setShield(int shield, int maxShield) {
    if (shield <= maxShield) this->shield = shield;
    if (shield < 0) isDead = true;
    else isDead = false;
}

int Ship::getShield() const {
    return shield;
}

void Ship::clean() {
    SDL_DestroyTexture(image);
}