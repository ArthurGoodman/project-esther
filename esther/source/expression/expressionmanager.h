#pragma once

#include "variant.h"
#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd();
    Expression *createAttributeAssignment();
    Expression *createBlock();
    Expression *createConstant();
    Expression *createContextResolution();
    Expression *createEmpty();
    Expression *createFunction();
    Expression *createHere();
    Expression *createIdentifier();
    Expression *createIf();
    Expression *createLiteral();
    Expression *createLocalAssignment();
    Expression *createLoop();
    Expression *createNot();
    Expression *createOr();
    Expression *createSelf();
};
