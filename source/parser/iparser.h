#pragma once

#include <list>

class Expression;
class Token;

typedef std::list<Token> Tokens;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
