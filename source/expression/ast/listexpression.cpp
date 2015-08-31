#include "listexpression.h"

#include "runtime.h"

ListExpression::ListExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *ListExpression::exec(Context *context) {
    Object *value = Runtime::getNull();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
