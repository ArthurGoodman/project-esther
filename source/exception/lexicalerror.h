#pragma once
#include "common.h"

#include "errorexception.h"

// This is used in lexical analysis.
class LexicalError : public ErrorException {
public:
    LexicalError(string message, Position getPosition);

    string message();
    void raise();
};
