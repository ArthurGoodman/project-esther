#pragma once
#include "common.h"

#include "position.h"

class PositionedObject {
protected:
    Position position;

public:
    PositionedObject(Position position = Position());

    Position getPosition();
    void setPosition(Position position);
};
