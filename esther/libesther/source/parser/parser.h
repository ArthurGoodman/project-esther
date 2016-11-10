#pragma once

#include <string>

#include "iparser.h"
#include "token.h"

class Parser : public IParser {
    std::list<Context *> contexts;
    Tokens tokens;
    Tokens::iterator token;

public:
    Expression *parse(Context *context, Tokens &tokens);

private:
    void error(const std::string &msg, int delta = 0);

    void getToken();

    bool check(int id);
    bool accept(int id);

    Context *context();

    std::list<Expression *> parseBlock();
    std::list<Expression *> parseList();

    Expression *parseIdentifier();

    Expression *oper();
    Expression *expr();
    Expression *logicOr();
    Expression *logicAnd();
    Expression *equality();
    Expression *relation();
    Expression *addSub();
    Expression *mulDiv();
    Expression *power();
    Expression *negate();
    Expression *preffix();
    Expression *suffix();
    Expression *term();
};
