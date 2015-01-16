#include "expression.h"

#include "defaultexpressionmanager.h"

namespace esther {

ExpressionManager *Expression::manager;

void Expression::initialize() {
    manager = new DefaultExpressionManager;
}

void Expression::release() {
    delete manager;
}
}
