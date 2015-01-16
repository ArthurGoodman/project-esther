#pragma once
#include <common.h>

#include "exception.h"
#include "position.h"

namespace esther {

class ErrorException : public Exception {
    string message;    // Error message.
    Position position; // Position of the error in code.

public:
    ErrorException(string msg, Position pos);

    virtual string msg();
    Position pos();
};
}
