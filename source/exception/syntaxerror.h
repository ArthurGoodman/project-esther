#pragma once
#include "common.h"

#include "errorexception.h"

class SyntaxError : public ErrorException {
public:
    SyntaxError(string message, Position getPosition);

    string message();
    void raise();
};
