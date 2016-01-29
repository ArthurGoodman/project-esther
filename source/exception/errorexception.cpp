#include "errorexception.h"

ErrorException::ErrorException(const std::string &message, Position position)
    : position(position), msg(message) {
}

std::string ErrorException::message() {
    return msg;
}

Position ErrorException::getPosition() {
    return position;
}

void ErrorException::setPosition(Position position) {
    this->position = position;
}
