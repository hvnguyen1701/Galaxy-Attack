#ifndef ITEM_H
#define ITEM_H

#include "BaseObject.h"

class Item: public BaseObject {
    const int SPEED = 1;
    bool isActive;

public:
    Item();
    ~Item();
    void setActivation(bool isActive);
    bool getActivation() const;
    void move(int screenHeight);
};

#endif