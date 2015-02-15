#include "tupleexpression.h"

#include "runtime.h"
#include "tuple.h"

TupleExpression::TupleExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

Object *TupleExpression::eval(Context *context) {
    list<Object *> evaledNodes;

    foreach (i, nodes)
        evaledNodes << (*i)->eval(context);

    return new Tuple(evaledNodes);
}
