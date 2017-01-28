#include "blockexpression.h"

#include "common.h"
#include "context.h"
#include "esther.h"

BlockExpression::BlockExpression(const std::list<Expression *> &nodes) {
    for (Expression *e : nodes)
        this->nodes << e;
}

BlockExpression::~BlockExpression() {
    for (Expression *e : nodes)
        delete e;
}

Object *BlockExpression::exec(Esther *esther) {
    Object *value = esther->getNull();

    for (Expression *e : nodes)
        value = e->eval(esther);

    return value;
}
