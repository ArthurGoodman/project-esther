#pragma once

#include <string>

#include "iparser.h"
#include "token.h"
#include "tokens.h"

class Esther;
class Object;

class Parser : public IParser {
    enum ContextType {
        RegularContext,
        ObjectContext
    };

    Esther *esther;

    Tokens tokens;
    Tokens::iterator token;

public:
    Expression *parse(Esther *esther, Tokens &tokens) override;

private:
    void error(const std::string &msg, int delta = 0);

    void getToken();

    bool check(int id);
    bool accept(int id);

    std::list<Expression *> block();
    std::list<Expression *> list();

    Expression *binOper(Expression *left, const std::string &oper, Expression *right);
    Expression *assignOper(Expression *left, const std::string &oper, Expression *right);
    Expression *call(Expression *self, Expression *f, int closingBracketId = tRPar);
    Expression *dot(Expression *e);

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
