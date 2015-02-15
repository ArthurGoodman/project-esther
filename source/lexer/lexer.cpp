#include "lexer.h"

#include "defaultlexer.h"

Lexer::~Lexer() {
}

Lexer *Lexer::create() {
    return new DefaultLexer;
}
