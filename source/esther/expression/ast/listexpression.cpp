#include "listexpression.h"

#include "runtime.h"

namespace esther {

ListExpression::ListExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *ListExpression::eval(Context *context) {
    Object *value = Runtime::getNull();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
}
