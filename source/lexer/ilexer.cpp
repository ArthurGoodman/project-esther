#include "ilexer.h"

#include "lexer.h"

ILexer *ILexer::lexer;

void ILexer::initialize() {
    lexer = new Lexer;
}

void ILexer::release() {
    delete lexer;
}

ILexer *ILexer::instance() {
    return lexer;
}

ILexer::~ILexer() {
}
