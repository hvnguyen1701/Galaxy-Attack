#include "../Headers/Bar.h"

using std::string;

Bar::Bar() {
    state = 0;
}

Bar::~Bar() {
    SDL_DestroyTexture(image);
}

void Bar::loadImage(const string &path, int numberStates) {
    BaseObject::loadImage(path);
    this->numberStates = numberStates;

    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    src = {0, 0, w, h/numberStates};
}

void Bar::setState(int state) {
    if (state >= 0 && state < numberStates) 
        this->state = state;

    src.y = (this->state)*src.h;
}

int Bar::getState() const {
    return state;
}