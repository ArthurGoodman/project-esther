#include "dynamiccallexpression.h"

#include "common.h"
#include "context.h"
#include "function.h"

DynamicCallExpression::DynamicCallExpression(Expression *self, Expression *body, const std::list<Expression *> &args)
    : self(self), body(body), args(args) {
}

DynamicCallExpression::~DynamicCallExpression() {
    delete self;
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *DynamicCallExpression::exec(Context *context) {
    Object *evaledSelf = self ? self->eval(context) : context->getSelf();
    Object *evaledBody = body->eval(context);

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    if (dynamic_cast<Function *>(evaledBody))
        return ((Function *)evaledBody)->invoke(evaledSelf, evaledArgs);

    evaledArgs.insert(evaledArgs.begin(), evaledSelf);

    return evaledBody->call("()", evaledArgs);
}
