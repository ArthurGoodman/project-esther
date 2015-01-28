#include "blockexpression.h"

#include "esther.h"
#include "context.h"

namespace esther {

BlockExpression::BlockExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

BlockExpression::~BlockExpression() {
    foreach (i, nodes)
        delete *i;
}

Object *BlockExpression::eval(Context *context) {
    Object *value = Esther::getNull();

    foreach (i, nodes)
        value = (*i)->eval(context->childContext());

    return value;
}
}
