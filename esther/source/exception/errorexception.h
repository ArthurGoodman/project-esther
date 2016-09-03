#pragma once

#include "exception.h"
#include "position.h"

class ErrorException : public Exception {
    Position position;
    std::string msg;

public:
    ErrorException(const std::string &message, Position position = Position());

    std::string message();

    Position getPosition();
    void setPosition(Position position);
};
