#include "lexicalerror.h"

LexicalError::LexicalError(string message, Position position)
    : ErrorException(message, position) {
}

string LexicalError::message() {
    return "lexical error: " + ErrorException::message();
}

void LexicalError::raise() {
    throw this;
}
