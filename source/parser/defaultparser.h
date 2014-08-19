#pragma once
#include "common.h"

#include "parser.h"

namespace Esther {

class Lexer;

class DefaultParser : public Parser
{
    Lexer *lexer;

public:
    DefaultParser();
    ~DefaultParser();

    Expression *parse();
};

}
