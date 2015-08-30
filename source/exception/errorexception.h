#pragma once
#include "common.h"

#include "exception.h"
#include "position.h"

class ErrorException : public Exception {
    string msg;
    Position pos;

public:
    ErrorException(string message, Position position = Position());

    string message();
    Position position();
};
