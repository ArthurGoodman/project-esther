#pragma once
#include "common.h"

#include "debug.h"
#include "expressionmanager.h"

#if DEBUG_PARSER

namespace esther {

class DebugExpressionManager : public ExpressionManager {
public:
    Expression *createEmpty();

    Expression *createBlock(list<Expression *> nodes);
    Expression *createList(list<Expression *> nodes);

    Expression *createLiteral(Object *value);

    Expression *createOr(Expression *self, Expression *arg);
    Expression *createAnd(Expression *self, Expression *arg);

    Expression *createNegate(Expression *self);

    Expression *createIdentifier(Expression *name);
    Expression *createIdentifierAssignment(Expression *name, Expression *value);
    Expression *createIdentifierDefinition(Expression *name, Expression *value);

    Expression *createCall(Expression *self, string name, list<Expression *> args);

    Expression *createCloneAndCall(Expression *self, string name);

    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    Expression *createDo(Expression *body, Expression *condition);

    Expression *createContextResolution(Expression *self, Expression *body);

    Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body);

    Expression *createReturn(Expression *value);
    Expression *createBreak(Expression *value);
    Expression *createContinue();
};
}

#endif
