#pragma once

#include <list>
#include <string>

#include "common.h"

class ILexer {
public:
    virtual ~ILexer();
    virtual Tokens lex(const std::string &source) = 0;
};
