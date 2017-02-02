#pragma once

#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd(Expression *self, Expression *arg) override;
    Expression *createAssignment(const std::string &name, Expression *value) override;
    Expression *createAttributeAssignment(Expression *self, const std::string &name, Expression *value) override;
    Expression *createAttribute(Expression *self, const std::string &name) override;
    Expression *createBlock(const std::list<Expression *> &nodes) override;
    Expression *createCall(Expression *f, Expression *self, int args) override;
    Expression *createClassDefinition(const std::string &name, Expression *superclass) override;
    Expression *createConstant(Ptr<Object> value) override;
    Expression *createContextResolution(Expression *self, Expression *body, Expression *here) override;
    Expression *createEmpty() override;
    Expression *createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) override;
    Expression *createHere() override;
    Expression *createIdentifier(const std::string &name) override;
    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) override;
    Expression *createLiteral(const Variant &value) override;
    Expression *createLocalAssignment(const std::string &name, Expression *value) override;
    Expression *createLoop(Expression *condition, Expression *body) override;
    Expression *createNot(Expression *self) override;
    Expression *createOr(Expression *self, Expression *arg) override;
    Expression *createPop(int count) override;
    Expression *createPush(Expression *arg) override;
    Expression *createSelf() override;
    Expression *createStack(int index) override;
};
