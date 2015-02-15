#include "syntaxerror.h"

SyntaxError::SyntaxError(string message, Position pos)
    : ErrorException(message, pos) {
}

string SyntaxError::message() {
    return "syntax error: " + ErrorException::message();
}

void SyntaxError::raise() {
    throw this;
}
