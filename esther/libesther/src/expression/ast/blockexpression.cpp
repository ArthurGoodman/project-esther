#include "expression/ast/blockexpression.h"

#include "common/common.h"
#include "runtime/context.h"
#include "esther.h"

namespace es {

BlockExpression::BlockExpression(const std::list<Expression *> &nodes) {
    for (Expression *e : nodes)
        if (dynamic_cast<BlockExpression *>(e)) {
            this->nodes.insert(this->nodes.end(), static_cast<BlockExpression *>(e)->nodes.begin(), static_cast<BlockExpression *>(e)->nodes.end());
            static_cast<BlockExpression *>(e)->nodes.clear();
            delete e;
        } else
            this->nodes << e;
}

BlockExpression::~BlockExpression() {
    for (Expression *e : nodes)
        delete e;
}

Object *BlockExpression::exec(Esther *esther) {
    Object *volatile value = esther->getNull();

    for (Expression *e : nodes)
        value = e->eval(esther);

    return value;
}
}
