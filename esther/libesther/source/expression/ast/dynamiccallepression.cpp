#include "dynamiccallepression.h"

#include "common.h"
#include "context.h"
#include "function.h"

DynamicCallEpression::DynamicCallEpression(Expression *body, const std::list<Expression *> &args)
    : body(body), args(args) {
}

DynamicCallEpression::~DynamicCallEpression() {
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *DynamicCallEpression::exec(Context *context) {
    std::vector<Object *> evaledArgs;

    Object *evaledBody = body->eval(context);

    if (dynamic_cast<Function *>(evaledBody)) {
        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return ((Function *)evaledBody)->invoke(context->getSelf(), evaledArgs);
    }

    evaledArgs << context->getSelf();

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    return evaledBody->call("()", evaledArgs);
}
