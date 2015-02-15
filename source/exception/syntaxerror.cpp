#include "syntaxerror.h"

SyntaxError::SyntaxError(string message, Position position)
    : ErrorException(message, position) {
}

string SyntaxError::message() {
    return "syntax error: " + ErrorException::message();
}

void SyntaxError::raise() {
    throw this;
}
