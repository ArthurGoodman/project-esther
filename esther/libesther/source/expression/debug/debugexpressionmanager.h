#pragma once

#include "common.h"
#include "iexpressionmanager.h"

#if DEBUG_PARSER

class DebugExpressionManager : public IExpressionManager {
public:
    Expression *createAnd();
    Expression *createAttributeAssignment();
    Expression *createBlock();
    Expression *createClass();
    Expression *createConstant();
    Expression *createContextResolution();
    Expression *createEmpty();
    Expression *createFunction();
    Expression *createIdentifier();
    Expression *createIf();
    Expression *createLiteral();
    Expression *createLocalAssignment();
    Expression *createLoop();
    Expression *createNot();
    Expression *createOr();
    Expression *createSelf();
};

#endif
