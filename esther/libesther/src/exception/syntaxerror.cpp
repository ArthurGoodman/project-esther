#include "exception/syntaxerror.h"

SyntaxError::SyntaxError(const std::string &message, Position position)
    : ErrorException(message, position) {
}

std::string SyntaxError::message() {
    return "syntax error: " + ErrorException::message();
}

void SyntaxError::raise() {
    throw this;
}
