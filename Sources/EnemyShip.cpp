#include "../Headers/EnemyShip.h"

EnemyShip::EnemyShip(SDL_Renderer *renderer, int screenWidth): Ship(renderer) {
    int x = rand()%(screenWidth - LENGTH_SIDE_TEXTURE + 1);
    int y = -LENGTH_SIDE_TEXTURE;
    dst = {x, y, LENGTH_SIDE_TEXTURE, LENGTH_SIDE_TEXTURE};
    isActive = true;

    isMovingLeft = rand()%2;
}

void EnemyShip::setActivation(bool isActive) {
    this->isActive = isActive;
}

bool EnemyShip::getActivation() const {
    return isActive;
}

void EnemyShip::move(int screenWidth, int screenHeight) {
    // Moving left right
    if (isMovingLeft) dst.x -= SPEED;
    else dst.x += SPEED;

    if (dst.x <= 0) isMovingLeft = false;
    else if (dst.x + dst.w >= screenWidth) isMovingLeft = true;
    
    // Moving forward
    dst.y += SPEED;
    if (dst.y > screenHeight) isActive = false;
}