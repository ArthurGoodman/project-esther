#include "iexpressionmanager.h"

#include "debugexpressionmanager.h"
#include "expressionmanager.h"

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
