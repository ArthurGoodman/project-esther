#pragma once
#include "common.h"

namespace esther {

class Exception {
    string msg;

public:
    Exception(string message = "");
    virtual ~Exception();

    virtual string message();

    virtual void raise() = 0;
};
}
