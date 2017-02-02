#pragma once

#include <list>
#include <string>

#include "common/common.h"
#include "common/token.h"

class ILexer {
public:
    static ILexer *instance();

    virtual ~ILexer();
    virtual Tokens &lex(const std::string &source) = 0;
};
