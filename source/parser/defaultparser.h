#pragma once
#include "common.h"

#include "parser.h"
#include "defaultlexer.h"

namespace esther {

class Lexer;

class DefaultParser : public Parser {
    Lexer *lexer;
    Tokens::iterator token;

public:
    DefaultParser();
    ~DefaultParser();

    Expression *parse(const string &source);

private:
    void error(string msg, int delta = 0);

    bool check(int id);
    bool accept(int id);
    bool range(int a, int b);

    void getToken();

    Expression *expr();
    Expression *assign();
    Expression *logicOr();
    Expression *logicXor();
    Expression *logicAnd();
    Expression *equality();
    Expression *relation();
    Expression *addSub();
    Expression *mulDiv();
    Expression *dot();
    Expression *preffix();
    Expression *suffix();
    Expression *arrow();
    Expression *term();
};
}
