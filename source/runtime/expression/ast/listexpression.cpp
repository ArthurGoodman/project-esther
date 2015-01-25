#include "listexpression.h"

#include "esther.h"

namespace esther {

ListExpression::ListExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *ListExpression::eval(Context *context) {
    Object *value = Esther::getNull();

    foreach (i, nodes)
        value = (*i)->eval(context);

    return value;
}
}
