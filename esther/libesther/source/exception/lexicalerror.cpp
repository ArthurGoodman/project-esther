#include "lexicalerror.h"

LexicalError::LexicalError(const std::string &message, Position position)
    : ErrorException(message, position) {
}

std::string LexicalError::message() {
    return "lexical error: " + ErrorException::message();
}

void LexicalError::raise() {
    throw this;
}