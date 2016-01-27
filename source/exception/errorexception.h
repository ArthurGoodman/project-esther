#pragma once
#include "common.h"

#include "exception.h"
#include "position.h"

class ErrorException : public Exception {
    Position position;
    string msg;

public:
    ErrorException(string message, Position position = Position());

    string message();

    Position getPosition();
    void setPosition(Position position);
};
