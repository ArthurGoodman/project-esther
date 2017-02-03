#include "lexer/ilexer.h"

#include "lexer/lexer.h"

namespace es {

ILexer *ILexer::instance() {
    static Lexer lexer;
    return &lexer;
}

ILexer::~ILexer() {
}
}
