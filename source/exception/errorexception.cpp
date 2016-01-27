#include "errorexception.h"

ErrorException::ErrorException(string message, Position position)
    : position(position), msg(message) {
}

string ErrorException::message() {
    return msg;
}

Position ErrorException::getPosition() {
    return position;
}

void ErrorException::setPosition(Position position) {
    this->position = position;
}
