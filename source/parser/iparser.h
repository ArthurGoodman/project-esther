#pragma once
#include "common.h"

class Expression;
class Token;

typedef list<Token> Tokens;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
