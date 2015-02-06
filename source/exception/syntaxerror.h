#pragma once
#include "common.h"

#include "errorexception.h"

namespace esther {

// This is used in syntax analysis.
class SyntaxError : public ErrorException {
public:
    SyntaxError(string msg, Position pos);

    string msg();

    void raise();
};
}
