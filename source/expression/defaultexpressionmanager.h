#pragma once
#include "common.h"

#include "expressionmanager.h"

class DefaultExpressionManager : public ExpressionManager {
public:
    Expression *createEmpty();

    Expression *createBlock(list<Expression *> nodes);
    Expression *createList(list<Expression *> nodes);

    Expression *createTuple(list<Expression *> nodes);

    Expression *createLiteral(Object *value);

    Expression *createOr(Expression *self, Expression *arg);
    Expression *createAnd(Expression *self, Expression *arg);

    Expression *createNegate(Expression *self);

    Expression *createPreDecrement(Expression *self);
    Expression *createPreIncrement(Expression *self);
    Expression *createPostDecrement(Expression *self);
    Expression *createPostIncrement(Expression *self);

    Expression *createIdentifier(Expression *name);
    Expression *createIdentifierAssignment(Expression *name, Expression *value);
    Expression *createIdentifierDefinition(Expression *type, Expression *name, Expression *value);

    Expression *createParameter(Expression *type, Expression *name, Expression *value);
    Expression *createCall(Expression *self, string name, list<Expression *> args);

    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody);
    //Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    Expression *createDo(Expression *body, Expression *condition);

    Expression *createContextResolution(Expression *self, Expression *body);

    Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body);

    Expression *createFunctionDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic);
    Expression *createMethodDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic);

    Expression *createReturn(Expression *value);
    Expression *createBreak(Expression *value);
    Expression *createContinue();

    Expression *createSelf();
    Expression *createHere();

    Expression *createStatic(Expression *body);
};
