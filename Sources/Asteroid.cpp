#include "../Headers/Asteroid.h"

Asteroid::Asteroid(SDL_Renderer *renderer, int screenWidth, int screenHeight): BaseObject(renderer) {
    dst.w = dst.h = 65;

    // Random left or right of the screen
    if (rand()%2 == 0) {
        isFromLeft = true;
        dst.x = -dst.w;
    }
    else {
        isFromLeft = false;
        dst.x = screenWidth + dst.w;
    }

    dst.y = rand()%(screenHeight - 9*screenHeight/10);
    isActive = true;
}

void Asteroid::setImage(SDL_Texture *image) {
    BaseObject::setImage(image);
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    src = {0, 0, w/NUMBER_COLUMNS_IMAGE, h/NUMBER_ROWS_IMAGE};
}

void Asteroid::setActivation(bool isActive) {
    this->isActive = isActive;
}

bool Asteroid::getActivation() const {
    return isActive;
}

void Asteroid::move(int screenWidth, int screenHeight) {
    dst.y += Y_SPEED;
    if (isFromLeft) {
        dst.x += X_SPEED;
        if (dst.x > screenWidth || dst.y > screenHeight) isActive = false;
    }
    else {
        dst.x -= X_SPEED;
        if (dst.x < 0 || dst.y > screenHeight) isActive = false;
    }
}

void Asteroid::animate() {
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