#include "iexpressionmanager.h"

#include "expression/debug/debugexpressionmanager.h"
#include "expression/expressionmanager.h"

IExpressionManager *IExpressionManager::instance() {
#if DEBUG_PARSER
    static DebugExpressionManager manager;
#else
    static ExpressionManager manager;
#endif

    return &manager;
}

IExpressionManager::~IExpressionManager() {
}
