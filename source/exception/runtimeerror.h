#pragma once
#include "common.h"

#include "errorexception.h"

class RuntimeError : public ErrorException {
public:
    RuntimeError(string message);

    string message();
    void raise();
};
