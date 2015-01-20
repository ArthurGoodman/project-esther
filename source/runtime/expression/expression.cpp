#include "expression.h"

#include "expressionmanager.h"

namespace esther {

ExpressionManager *Expression::manager;

void Expression::initialize() {
    manager = ExpressionManager::create();
}

void Expression::release() {
    delete manager;
}
}
