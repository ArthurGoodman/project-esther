#include "dynamiccallexpression.h"

#include "common.h"
#include "context.h"
#include "function.h"

DynamicCallExpression::DynamicCallExpression(Expression *body, const std::list<Expression *> &args)
    : body(body)
    , args(args) {
}

DynamicCallExpression::~DynamicCallExpression() {
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *DynamicCallExpression::exec(Context *context) {
    Object *f = body->eval(context);

    if (dynamic_cast<Function *>(f)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return ((Function *)f)->invoke(context->getSelf(), evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << context->getSelf();

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return f->call("()", evaledArgs);
    }
}
