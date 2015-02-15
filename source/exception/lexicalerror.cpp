#include "lexicalerror.h"

LexicalError::LexicalError(string message, Position pos)
    : ErrorException(message, pos) {
}

string LexicalError::message() {
    return "lexical error: " + ErrorException::message();
}

void LexicalError::raise() {
    throw this;
}
