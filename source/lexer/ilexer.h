#pragma once

#include "token.h"

class ILexer {
public:
    static ILexer *instance();

    virtual ~ILexer();
    virtual Tokens &lex(const std::string &source) = 0;
};
