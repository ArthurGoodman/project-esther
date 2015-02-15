#pragma once
#include "common.h"

class Exception {
public:
    virtual ~Exception();

    virtual string message();
    virtual void raise() = 0;
};
