#include "../Headers/Button.h"

using std::string;

Button::Button() {}

Button::~Button() {
    SDL_DestroyTexture(image);
}

void Button::loadImage(const string &path) {
    BaseObject::loadImage(path);
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    src = {0, 0, w/2, h};
}

bool Button::isMouseOnButton(int mouseX, int mouseY) {
    if (mouseX >= dst.x && mouseX <= dst.x + dst.w &&
        mouseY >= dst.y && mouseY <= dst.y + dst.h) return true;
    src.x = 0;
    return false;
}

void Button::animate() {
    src.x = src.w;
}
