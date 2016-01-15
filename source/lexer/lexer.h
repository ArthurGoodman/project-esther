#pragma once
#include "common.h"

#include "debug.h"
#include "ilexer.h"

class Lexer : public ILexer {
    static vector<string> operators;
    static vector<string> keywords;

#if DEBUG_LEXER
    static vector<string> tokenTypes;
#endif

    Tokens tokens;

    const string *source;
    Token token;
    int pos, line, column;

public:
    Tokens &lex(const string &source);

private:
    template <int N>
    static int count(string(&)[N]);

    void error(string msg, int shift = 0);
    void scan();
    void skipSpacesExceptForNewLine();
    void skipSpaces();
    const char &at(int pos);
};
