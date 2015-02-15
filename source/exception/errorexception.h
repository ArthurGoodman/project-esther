#pragma once
#include "common.h"

#include "exception.h"
#include "position.h"

class ErrorException : public Exception {
    string msg;
    Position pos; // Position of error in the code.

public:
    ErrorException(string message, Position position = Position());

    string message();
    Position position();
};
