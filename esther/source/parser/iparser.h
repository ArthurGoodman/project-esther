#pragma once

#include <list>

class Token;
class Expression;

typedef std::list<Token> Tokens;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
