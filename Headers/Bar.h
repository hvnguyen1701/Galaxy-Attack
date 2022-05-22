#ifndef BAR_H
#define BAR_H

#include "BaseObject.h"

class Bar: public BaseObject {
    int numberStates, state;

public:
    Bar();
    ~Bar();
    void loadImage(const std::string &path, int numberStates);
    void setState(int state);
    int getState() const;
};

#endif