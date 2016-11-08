#pragma once

#include "common.h"
#include "iexpressionmanager.h"

#if DEBUG_PARSER

class DebugExpression;

class DebugExpressionManager : public IExpressionManager {
    static std::vector<const char *> typenames;

public:
    Expression *createAnd(Expression *self, Expression *arg);
    Expression *createAttributeAssignment(Expression *name, Expression *value);
    Expression *createBlock(const std::list<Expression *> &nodes);
    Expression *createCall(Expression *name, const std::list<Expression *> &args);
    Expression *createConstant(Object *value);
    Expression *createContextResolution(Expression *self, Expression *body, Context *context);
    Expression *createDirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args);
    Expression *createDynamicCall(Expression *body, const std::list<Expression *> &args);
    Expression *createEmpty();
    Expression *createHere();
    Expression *createIdentifier(Expression *name);
    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createLiteral(const Variant &value);
    Expression *createLocalAssignment(Expression *name, Expression *value);
    Expression *createLoop(Expression *condition, Expression *body);
    Expression *createNot(Expression *self);
    Expression *createOr(Expression *self, Expression *arg);
    Expression *createSelf();

private:
    static DebugExpression *literal(const std::string &type, const std::string &value);
};

#endif
