#pragma once

#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd(Expression *self, Expression *arg);
    Expression *createAssignment(const std::string &name, Expression *value);
    Expression *createAttributeAssignment(Expression *self, const std::string &name, Expression *value);
    Expression *createAttribute(Expression *self, const std::string &name);
    Expression *createBlock(const std::list<Expression *> &nodes);
    Expression *createCall(Expression *f, Expression *self, int args);
    Expression *createClassDefinition(const std::string &name, Expression *superclass);
    Expression *createConstant(Object *value);
    Expression *createContextResolution(Expression *self, Expression *body, Expression *here);
    Expression *createEmpty();
    Expression *createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body);
    Expression *createHere();
    Expression *createIdentifier(const std::string &name);
    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createLiteral(const Variant &value);
    Expression *createLocalAssignment(const std::string &name, Expression *value);
    Expression *createLoop(Expression *condition, Expression *body);
    Expression *createNot(Expression *self);
    Expression *createOr(Expression *self, Expression *arg);
    Expression *createPop(int count);
    Expression *createPush(Expression *arg);
    Expression *createSelf();
    Expression *createStack(int index);
};
