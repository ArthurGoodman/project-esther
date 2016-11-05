#pragma once

#include "variant.h"
#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd(Expression *self, Expression *arg);
    Expression *createAttributeAssignment();
    Expression *createBlock();
    Expression *createConstant(Object *value);
    Expression *createContextResolution();
    Expression *createEmpty();
    Expression *createFunction();
    Expression *createHere();
    Expression *createIdentifier();
    Expression *createIf();
    Expression *createLiteral(const Variant &value);
    Expression *createLocalAssignment();
    Expression *createLoop();
    Expression *createNot();
    Expression *createOr(Expression *self, Expression *arg);
    Expression *createSelf();
};
