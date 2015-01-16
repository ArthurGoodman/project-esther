#include "lexicalerror.h"

namespace esther {

LexicalError::LexicalError(string msg, Position pos)
    : ErrorException(msg, pos) {
}

string LexicalError::msg() {
    return "lexical error: " + ErrorException::msg();
}

void LexicalError::raise() {
    throw this;
}
}
