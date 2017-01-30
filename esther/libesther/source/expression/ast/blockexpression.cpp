#include "blockexpression.h"

#include "common.h"
#include "context.h"
#include "esther.h"

BlockExpression::BlockExpression(const std::list<Expression *> &nodes) {
    for (Expression *e : nodes)
        if (dynamic_cast<BlockExpression *>(e)) {
            this->nodes.insert(this->nodes.end(), ((BlockExpression *)e)->nodes.begin(), ((BlockExpression *)e)->nodes.end());
            ((BlockExpression *)e)->nodes.clear();
            delete e;
        } else
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
