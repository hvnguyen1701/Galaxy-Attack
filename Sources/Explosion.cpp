#include "../Headers/Explosion.h"

Explosion::Explosion() {}

Explosion::Explosion(SDL_Renderer *renderer): BaseObject(renderer) {
    dst.w = dst.h = 150;
    isActive = false;
}

void Explosion::setImage(SDL_Texture *image, int numberRowsImage, int numberColumnsImage) {
    BaseObject::setImage(image);
    this->numberRowsImage = numberRowsImage;
    this->numberColumnsImage = numberColumnsImage;
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    src = {0, 0, w/numberColumnsImage, h/numberRowsImage};
}

void Explosion::setActivation(bool isActive) {
    this->isActive = isActive;
    iRow = jColumn = 0;
}

bool Explosion::getActivation() const {
    return isActive;
}

void Explosion::animate() {
    src.x = src.w*jColumn;
    src.y = src.h*iRow;

    if (iRow >= numberRowsImage - 1 && jColumn >= numberColumnsImage - 1) {
        isActive = false;
        return;
    }

    count++;
    if (count == DISTANCE_BETWEEN_2_IMAGES) {
        jColumn++;
        if (jColumn >= numberColumnsImage) {
            jColumn = 0;
            iRow = (iRow + 1)%numberRowsImage;
        }
        count = 0;
    }
}