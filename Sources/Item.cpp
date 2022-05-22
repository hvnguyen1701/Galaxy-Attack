#include "../Headers/Item.h"

Item::Item() {
    dst.w = dst.h = 50;
}

Item::~Item() {
    SDL_DestroyTexture(image);
}

void Item::setActivation(bool isActive) {
    this->isActive = isActive;
}

bool Item::getActivation() const {
    return isActive;
}

void Item::move(int screenHeight) {
    dst.y += SPEED;
    if (dst.y > screenHeight) isActive = false;
}