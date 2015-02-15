#include "blockexpression.h"

#include "runtime.h"
#include "context.h"

BlockExpression::BlockExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

BlockExpression::~BlockExpression() {
    foreach (i, nodes)
        delete *i;
}

Object *BlockExpression::eval(Context *context) {
    Object *value = Runtime::getNull();

    context = context->childContext();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
