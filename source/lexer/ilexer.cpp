#include "ilexer.h"

#include "lexer.h"

ILexer *ILexer::instance() {
    static Lexer lexer;
    return &lexer;
}

ILexer::~ILexer() {
}
