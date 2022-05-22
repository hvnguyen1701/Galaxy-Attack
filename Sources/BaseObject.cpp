#include "../Headers/BaseObject.h"

using std::string;

BaseObject::BaseObject() {
    image = nullptr;
    src = {-1, -1, -1, -1};
}

BaseObject::BaseObject(SDL_Renderer *renderer) {
    image = nullptr;
    src = {-1, -1, -1, -1};
    this->renderer = renderer;
}

void BaseObject::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void BaseObject::loadImage(const string &path) {
    image = IMG_LoadTexture(renderer, path.c_str());
}

void BaseObject::setImage(SDL_Texture *image) {
    this->image = image;
}

void BaseObject::setPositionDst(int x, int y) {
    dst.x = x;
    dst.y = y;
}

void BaseObject::setWidthHeightDst(int w, int h) {
    dst.w = w;
    dst.h = h;
}

SDL_Rect BaseObject::getDst() const {
    return dst;
}

int BaseObject::getWidthDst() const {
    return dst.w;
}

int BaseObject::getHeightDst() const {
    return dst.h;
}

void BaseObject::render() const {
    SDL_RenderCopy(renderer, image, (src.x == -1) ? nullptr : &src, &dst);
}