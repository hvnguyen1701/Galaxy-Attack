#include "../Headers/Background.h"

using std::string;

Background::Background() {
    dst = {-1, -1, -1, -1};
    nextDst = {-1, -1, -1, -1};
}

Background::~Background() {
    SDL_DestroyTexture(image);
}

void Background::setValueDst(int x, int y, int w, int h) {
    dst = {x, y, w, h};
}

void Background::setValueNextDst(int x, int y, int w, int h) {
    nextDst = {x, y, w, h};
}

void Background::slip(int speed, int screenHeight) {
    dst.y += speed;
    nextDst.y += speed;
    if (dst.y >= screenHeight) dst.y = nextDst.y - screenHeight;
    if (nextDst.y >= screenHeight) nextDst.y = dst.y - screenHeight;
}

void Background::render() const {
    SDL_RenderCopy(renderer, image, (src.x == -1) ? nullptr : &src, (dst.x == -1) ? nullptr : &dst);
    SDL_RenderCopy(renderer, image, (src.x == -1) ? nullptr : &src, (nextDst.x == -1) ? nullptr : &nextDst);
}