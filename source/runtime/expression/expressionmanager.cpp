#include "expressionmanager.h"

#include "debugexpressionmanager.h"
#include "defaultexpressionmanager.h"

namespace esther {

ExpressionManager *ExpressionManager::create() {
#if DEBUG_PARSER
    return new DebugExpressionManager;
#endif
    //    return new DefaultExpressionManager;
}

ExpressionManager::~ExpressionManager() {
}
}
