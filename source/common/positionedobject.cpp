#include "positionedobject.h"

PositionedObject::PositionedObject(Position position)
    : position(position) {
}

Position PositionedObject::getPosition() {
    return position;
}

void PositionedObject::setPosition(Position position) {
    this->position = position;
}
