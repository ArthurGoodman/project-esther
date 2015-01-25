#include "blockexpression.h"

#include "esther.h"

namespace esther {

BlockExpression::BlockExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *BlockExpression::eval(Context *context) {
    Object *value = Esther::getNull();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
}
