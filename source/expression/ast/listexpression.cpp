#include "listexpression.h"

#include "runtime.h"

ListExpression::ListExpression(std::list<Expression *> nodes)
    : nodes(nodes) {
}

IObject *ListExpression::exec(Context *context) {
    IObject *value = Runtime::getNull();

    for (Expression *e : nodes)
        value = e->eval(context);

    return value;
}
