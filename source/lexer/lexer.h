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

    Tokens tokens; // List of tokens, that the lexer produces.

    const string *source;
    Token token;           // Current token.
    int pos, line, column; // Current position of the lexer.

public:
    Tokens &lex(const string &source);

private:
    template <int N>
    static int count(string(&)[N]);

    void error(string msg, int shift = 0); // Handle lexical errors.
    void scan();                           // Scan code for the next lexeme.
    void skipSpaces();
    const char &at(int pos);
};
