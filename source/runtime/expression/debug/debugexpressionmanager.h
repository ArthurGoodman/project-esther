#pragma once
#include <common.h>
#include <debug.h>

#include "expressionmanager.h"

#if DEBUG_PARSER

namespace esther {

class DebugExpressionManager : public ExpressionManager {
public:
    Expression *createBlock(list<Expression *> nodes);
    Expression *createList(list<Expression *> nodes);

    Expression *createLiteral(Object *value);

    Expression *createCall(Expression *self, string name, list<Expression *> args);

    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    Expression *createDo(Expression *body, Expression *condition);
};
}

#endif
