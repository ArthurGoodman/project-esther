#pragma once

#include <list>
#include <string>

class Token;

typedef std::list<Token> Tokens;

class ILexer {
public:
    static ILexer *instance();

    virtual ~ILexer();
    virtual Tokens &lex(const std::string &source) = 0;
};
