#pragma once
#include "common.h"

#include "token.h"

// Lexical analysis.
class Lexer {
    static Lexer *lexer;

public:
    static void initialize();
    static void release();

    static Lexer *instance();

    virtual ~Lexer();
    virtual Tokens &lex(const string &source) = 0;
};
