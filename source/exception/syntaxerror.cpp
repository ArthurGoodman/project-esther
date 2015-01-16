#include "syntaxerror.h"

namespace esther {

SyntaxError::SyntaxError(string msg, Position pos)
    : ErrorException(msg, pos) {
}

string SyntaxError::msg() {
    return "syntax error: " + ErrorException::msg();
}

void SyntaxError::raise() {
    throw this;
}
}
