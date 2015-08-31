#include "blockexpression.h"

#include "runtime.h"
#include "context.h"

BlockExpression::BlockExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *BlockExpression::exec(Context *context) {
    Object *value = Runtime::getNull();

    context = context->childContext();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
