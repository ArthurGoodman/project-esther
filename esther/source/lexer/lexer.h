#pragma once

#include "ilexer.h"

class Lexer : public ILexer {
public:
    Tokens lex(const std::string &source);
};
