#pragma once
#include "common.h"

class Expression;
class Token;

typedef list<Token> Tokens;

// Syntactic analysis.
class IParser {
    static IParser *parser;

public:
    static void initialize();
    static void release();

    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
