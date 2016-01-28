#pragma once
#include "common.h"

#include "errorexception.h"

class LexicalError : public ErrorException {
public:
    LexicalError(string message, Position getPosition);

    string message();
    void raise();
};
