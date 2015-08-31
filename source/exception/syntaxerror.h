#pragma once
#include "common.h"

#include "errorexception.h"

// This is used in syntactic analysis.
class SyntaxError : public ErrorException {
public:
    SyntaxError(string message, Position getPosition);

    string message();
    void raise();
};
