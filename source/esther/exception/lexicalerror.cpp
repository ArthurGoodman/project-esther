#include "lexicalerror.h"

namespace esther {

LexicalError::LexicalError(string message, Position pos)
    : ErrorException(message, pos) {
}

string LexicalError::message() {
    return "lexical error: " + Exception::message();
}

void LexicalError::raise() {
    throw this;
}
}
