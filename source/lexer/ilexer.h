#pragma once
#include "common.h"

#include "token.h"

class ILexer {
    static ILexer *lexer;

public:
    static void initialize();
    static void release();

    static ILexer *instance();

    virtual ~ILexer();
    virtual Tokens &lex(const string &source) = 0;
};
