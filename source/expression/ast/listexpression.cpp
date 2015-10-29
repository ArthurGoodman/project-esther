#include "listexpression.h"

#include "runtime.h"

ListExpression::ListExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *ListExpression::exec(Context *context) {
    Object *value = Runtime::getNull();

    for (Expression *e : nodes)
        value = e->eval(context);

    return value;
}
