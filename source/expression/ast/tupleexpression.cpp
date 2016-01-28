#include "tupleexpression.h"

#include "runtime.h"
#include "tuple.h"

TupleExpression::TupleExpression(list<Expression *> nodes)
    : nodes(nodes) {
}

list<Expression *> TupleExpression::getNodes() {
    return nodes;
}

IObject *TupleExpression::exec(Context *context) {
    list<IObject *> evaledNodes;

    for (Expression *e : nodes)
        evaledNodes << e->eval(context);

    return new Tuple(evaledNodes);
}
