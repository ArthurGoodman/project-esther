#pragma once
#include <common.h>

#include "token.h"

namespace esther {

// Lexical analysis.
class Lexer {
public:
    static Lexer *create();

    virtual ~Lexer();
    virtual Tokens &lex(const string &source) = 0;
};
}
