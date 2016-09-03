#pragma once

#include <vector>

#include "debug.h"
#include "ilexer.h"

class Lexer : public ILexer {
    static std::vector<std::string> operators;
    static std::vector<std::string> keywords;

#if DEBUG_LEXER
    static std::vector<std::string> tokenTypes;
#endif

    Tokens tokens;

    const std::string *source;
    Token token;
    int pos, line, column;

public:
    Tokens &lex(const std::string &source);

private:
    template <int N>
    static int count(std::string(&)[N]);

    void error(const std::string &msg, int shift = 0);
    void scan();
    void skipSpacesExceptForNewLine();
    void skipSpaces();
    const char &at(int pos);
};
