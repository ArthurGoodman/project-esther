#include "exception/syntaxerror.h"

namespace es {

SyntaxError::SyntaxError(const std::string &message, Position position)
    : ErrorException(message, position) {
}

std::string SyntaxError::message() {
    return "syntax error: " + ErrorException::message();
}

void SyntaxError::raise() {
    throw this;
}
}
