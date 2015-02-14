#pragma once
#include "common.h"

#include "errorexception.h"

namespace esther {

// This is used in lexical analysis.
class LexicalError : public ErrorException {
public:
    LexicalError(string message, Position pos);

    string message();

    void raise();
};
}
