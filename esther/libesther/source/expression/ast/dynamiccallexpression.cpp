#include "dynamiccallexpression.h"

#include "common.h"
#include "context.h"
#include "function.h"
#include "esther.h"

DynamicCallExpression::DynamicCallExpression(Expression *body, const std::list<Expression *> &args)
    : body(body)
    , args(args) {
}

DynamicCallExpression::~DynamicCallExpression() {
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *DynamicCallExpression::exec(Esther *esther) {
    Object *f = body->eval(esther);

    if (dynamic_cast<Function *>(f)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return ((Function *)f)->invoke(esther, esther->context()->getSelf(), evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << esther->context()->getSelf();

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return f->call(esther, "()", evaledArgs);
    }
}
