#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"

class Button: public BaseObject {
    const int NUMBER_STATES = 2;

public:
    Button();
    ~Button();
    void loadImage(const std::string &path);
    bool isMouseOnButton(int mouseX, int mouseY);
    void animate();
};

#endif