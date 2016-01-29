#pragma once

#include "iparser.h"
#include "lexer.h"

class ILexer;

class Parser : public IParser {
    Tokens tokens;
    Tokens::iterator token;

    bool lastAcceptedNewLine;

public:
    Expression *parse(Tokens &tokens);

private:
    void error(const std::string &msg, int delta = 0);

    bool check(int id);
    bool realCheck(int id);
    bool accept(int id);
    bool realAccept(int id);

    void getToken();

    std::list<Expression *> parseBlock();
    std::list<Expression *> parseList();

    Expression *parseIdentifier(bool &dynamic);

    Expression *oper();
    Expression *context();
    Expression *expr();
    Expression *tuple();
    Expression *logicOr();
    Expression *logicAnd();
    Expression *equality();
    Expression *relation();
    Expression *range();
    Expression *addSub();
    Expression *mulDiv();
    Expression *power();
    Expression *negate();
    Expression *dot();
    Expression *preffix();
    Expression *suffix();
    Expression *term();
};
