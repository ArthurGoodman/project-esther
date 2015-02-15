#pragma once
#include "common.h"

#include "exception.h"

class OutOfRangeException : public Exception {
public:
    string message();
    void raise();
};
