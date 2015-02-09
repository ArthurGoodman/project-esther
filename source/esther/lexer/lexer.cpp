#include "lexer.h"

#include "defaultlexer.h"

namespace esther {

Lexer::~Lexer() {
}

Lexer *Lexer::create() {
    return new DefaultLexer;
}
}
