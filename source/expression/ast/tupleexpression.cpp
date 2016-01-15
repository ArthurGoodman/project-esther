#include "tupleexpression.h"

#include "runtime.h"
#include "tuple.h"

TupleExpression::TupleExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

list<Expression *> TupleExpression::getNodes() {
    return nodes;
}

Object *TupleExpression::exec(Context *context) {
    list<Object *> evaledNodes;

    for (Expression *e : nodes)
        evaledNodes << e->eval(context);

    return new Tuple(evaledNodes);
}
