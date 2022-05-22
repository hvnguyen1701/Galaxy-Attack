#include "../Headers/Gate.h"

Gate::Gate() {
    dst.w = dst.h = 150;
    isActive = false;
}

Gate::~Gate() {
    SDL_DestroyTexture(image);
}

void Gate::setActivation(bool isActive) {
    if (isActive) {
        int w, h;
        SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
        src = {0, 0, w/NUMBER_COLUMNS_IMAGE, h/NUMBER_ROWS_IMAGE};
    }
    this->isActive = isActive;
    count = 0;
    iRow = jColumn = 0;
}

bool Gate::getActivation() const {
    return isActive;
}

void Gate::move(int screenHeight) {
    dst.y += SPEED;
    if (dst.y > screenHeight) isActive = false;
}

void Gate::animate() {
    src.x = src.w*jColumn;
    src.y = src.h*iRow;

    count++;
    if (count == DISTANCE_BETWEEN_2_IMAGES) {
        jColumn++;
        if (jColumn >= NUMBER_COLUMNS_IMAGE) {
            jColumn = 0;
            iRow = (iRow + 1)%NUMBER_ROWS_IMAGE;
        }
        count = 0;
    }
}