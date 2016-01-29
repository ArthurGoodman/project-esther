#include "tupleexpression.h"

#include "common.h"
#include "runtime.h"
#include "tuple.h"

TupleExpression::TupleExpression(std::list<Expression *> nodes)
    : nodes(nodes) {
}

std::list<Expression *> TupleExpression::getNodes() {
    return nodes;
}

IObject *TupleExpression::exec(Context *context) {
    std::list<IObject *> evaledNodes;

    for (Expression *e : nodes)
        evaledNodes << e->eval(context);

    return new Tuple(evaledNodes);
}
