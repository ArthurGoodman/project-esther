#include "dynamiccallexpression.h"

#include "common.h"
#include "context.h"
#include "function.h"

DynamicCallExpression::DynamicCallExpression(Expression *body, const std::list<Expression *> &args)
    : body(body), args(args) {
}

DynamicCallExpression::~DynamicCallExpression() {
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *DynamicCallExpression::exec(Context *context) {
    Object *evaledBody = body->eval(context);

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    if (dynamic_cast<Function *>(evaledBody))
        return ((Function *)evaledBody)->invoke(context->getSelf(), evaledArgs);

    evaledArgs.insert(evaledArgs.begin(), context->getSelf());

    return evaledBody->call("()", evaledArgs);
}
