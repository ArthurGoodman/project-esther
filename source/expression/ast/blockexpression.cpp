#include "blockexpression.h"

#include "iobject.h"
#include "runtime.h"
#include "context.h"

BlockExpression::BlockExpression(std::list<Expression *> nodes)
    : nodes(nodes) {
}

IObject *BlockExpression::exec(Context *context) {
    IObject *value = Runtime::getNull();

    context = context->childContext();

    for (Expression *e : nodes)
        value = e->eval(context);

    return value;
}
