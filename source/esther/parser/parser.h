#pragma once
#include "common.h"

namespace esther {

class Expression;
class Token;

typedef list<Token> Tokens;

// Syntactic analysis.
class Parser {
public:
    static Parser *create();

    virtual ~Parser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
}
