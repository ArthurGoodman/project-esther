#include "expressionmanager.h"

#include "defaultexpressionmanager.h"

namespace esther {

ExpressionManager *ExpressionManager::create() {
    return new DefaultExpressionManager;
}

ExpressionManager::~ExpressionManager() {
}
}
