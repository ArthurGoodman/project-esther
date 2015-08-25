#pragma once
#include "common.h"

#include "parser.h"
#include "defaultlexer.h"

class Lexer;

class DefaultParser : public Parser {
    Tokens tokens;
    Tokens::iterator token;

public:
    Expression *parse(Tokens &tokens);

private:
    void error(string msg, int delta = 0);

    bool check(int id);
    bool accept(int id);

    void getToken();

    list<Expression *> parseBlock();
    list<Expression *> parseList();

    Expression *parseIdentifier();

    Expression *oper();
    Expression *context();
    Expression *expr();
    Expression *tuple();
    Expression *logicOr();
    Expression *logicAnd();
    Expression *equality();
    Expression *relation();
    Expression *addSub();
    Expression *mulDiv();
    Expression *power();
    Expression *dot();
    Expression *preffix();
    Expression *suffix();
    Expression *term();
};
