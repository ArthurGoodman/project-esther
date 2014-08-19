#pragma once
#include <common.h>

#include "token.h"

namespace Esther {

// Lexical analysis.
class Lexer
{
public:
    virtual ~Lexer();
    virtual Tokens lex() = 0;
};

}
