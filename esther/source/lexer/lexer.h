#pragma once

#include "ilexer.h"

class Lexer : public ILexer {
    Tokens tokens;

public:
    Tokens &lex(const std::string &source);
};
