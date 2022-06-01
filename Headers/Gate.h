#ifndef GATE_H
#define GATE_H

#include "BaseObject.h"

class Gate: public BaseObject {
    const int SPEED = 1;
    const int DISTANCE_BETWEEN_2_IMAGES = 4;
    const int NUMBER_ROWS_IMAGE = 1;
    const int NUMBER_COLUMNS_IMAGE = 16;
    
    int count, iRow, jColumn;
    bool isActive;

public:
    Gate();
    ~Gate();
    void setActivation(bool isActive);
    bool getActivation() const;
    void move(int screenHeight);
    void animate();
};

#endif