#pragma once
#include "common.h"

#include "exception.h"

class ContinueException : public Exception {
public:
    void raise();
};
