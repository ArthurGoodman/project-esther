#pragma once
#include "common.h"

#include "token.h"

class ILexer {
public:
    static ILexer *instance();

    virtual ~ILexer();
    virtual Tokens &lex(const string &source) = 0;
};
