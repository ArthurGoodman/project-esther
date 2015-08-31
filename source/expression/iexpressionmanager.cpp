#include "iexpressionmanager.h"

#include "debugexpressionmanager.h"
#include "expressionmanager.h"

IExpressionManager *IExpressionManager::create() {
#if DEBUG_PARSER
    return new DebugExpressionManager;
#endif
    return new ExpressionManager;
}

IExpressionManager::~IExpressionManager() {
}
