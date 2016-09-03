#pragma once

#include "debug.h"
#include "iexpressionmanager.h"

#if DEBUG_PARSER

class DebugExpressionManager : public IExpressionManager {
public:
    Expression *createEmpty();

    //    Expression *createBlock(std::list<Expression *> nodes);
    //    Expression *createList(std::list<Expression *> nodes);

    //    Expression *createTuple(std::list<Expression *> nodes);
    //    Expression *createAssignment(Expression *expresion, Expression *value);

    //    Expression *createLiteral(const Variant &value);
    //    Expression *createConstant(IObject *value);

    //    Expression *createOr(Expression *self, Expression *arg);
    //    Expression *createAnd(Expression *self, Expression *arg);

    //    Expression *createNegate(Expression *self);

    //    Expression *createPreDecrement(Expression *self);
    //    Expression *createPreIncrement(Expression *self);
    //    Expression *createPostDecrement(Expression *self);
    //    Expression *createPostIncrement(Expression *self);

    //    Expression *createIdentifier(Expression *name, bool dynamic);
    //    Expression *createIdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic);

    //    Expression *createParameter(Expression *type, Expression *name, Expression *value, bool dynamic);
    //    Expression *createCall(Expression *self, const std::string &name, std::list<Expression *> args);

    //    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    //    Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody);
    //    Expression *createFor(Expression *param, Expression *expression, Expression *body);
    //    Expression *createDo(Expression *body, Expression *condition);

    //    Expression *createContextResolution(Expression *self, Expression *body);
    //    Expression *createContextCall(Expression *self, Expression *body, std::list<Expression *> args);

    //    Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body);

    //    Expression *createFunctionDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);
    //    Expression *createMethodDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    //    Expression *createReturn(Expression *value);
    //    Expression *createBreak(Expression *value);
    //    Expression *createContinue();

    //    Expression *createSelf();
    //    Expression *createHere();

    //    Expression *createStatic(Expression *body);
    //    Expression *createInclude(Expression *fileName);
    //    Expression *createObjectLiteral(Expression *body);
};

#endif