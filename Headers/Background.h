#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "BaseObject.h"

class Background: public BaseObject {
    SDL_Rect nextDst;

public:
    Background();
    ~Background();
    void setValueDst(int x, int y, int w, int h);
    void setValueNextDst(int x, int y, int w, int h);
    void slip(int speed, int screenHeight);
    void render() const;
};

#endif