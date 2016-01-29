#pragma once

#include "exception.h"

class OutOfRangeException : public Exception {
public:
    std::string message();
    void raise();
};
