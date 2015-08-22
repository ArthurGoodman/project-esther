#include "lexer.h"

#include "defaultlexer.h"

Lexer *Lexer::lexer;

void Lexer::initialize() {
    lexer = new DefaultLexer;
}

void Lexer::release() {
    delete lexer;
}

Lexer *Lexer::instance() {
    return lexer;
}

Lexer::~Lexer() {
}
