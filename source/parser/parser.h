#pragma once
#include "common.h"

class Expression;
class Token;

typedef list<Token> Tokens;

// Syntactic analysis.
class Parser {
    static Parser *parser;

public:
    static void initialize();
    static void release();

    static Parser *instance();

    virtual ~Parser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
