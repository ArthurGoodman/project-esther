#pragma once
#include "common.h"

#include "exception.h"
#include "position.h"

namespace esther {

class ErrorException : public Exception {
    Position position; // Position of the error in code.

public:
    ErrorException(string message, Position pos = Position());

    Position pos();
};
}
