#include "syntaxerror.h"

namespace esther {

SyntaxError::SyntaxError(string message, Position pos)
    : ErrorException(message, pos) {
}

string SyntaxError::message() {
    return "syntax error: " + Exception::message();
}

void SyntaxError::raise() {
    throw this;
}
}
