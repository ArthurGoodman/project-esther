#include "blockexpression.h"

#include "common.h"
#include "context.h"
#include "runtime.h"

BlockExpression::BlockExpression(const std::list<Expression *> &nodes) {
    for (Expression *e : nodes)
        this->nodes << e;
}

BlockExpression::~BlockExpression() {
    for (Expression *e : nodes)
        delete e;
}

Object *BlockExpression::exec(Context *context) {
    Object *value = context->getRuntime()->getNull();

    for (Expression *e : nodes)
        value = e->eval(context);

    return value;
}
