#pragma once
#include <common.h>

namespace esther {

class Expression;
class Object;

class ExpressionManager {
public:
    static ExpressionManager *create();

    virtual ~ExpressionManager();

    virtual Expression *createBlock(list<Expression *> nodes) = 0;
    virtual Expression *createList(list<Expression *> nodes) = 0;

    virtual Expression *createLiteral(Object *value) = 0;

    virtual Expression *createCall(Expression *self, string name, list<Expression *> args) = 0;

    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) = 0;
    virtual Expression *createDo(Expression *body, Expression *condition) = 0;
};
}
