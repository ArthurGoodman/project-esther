#include "callexpression.h"

#include "context.h"
#include "runtime.h"
#include "function.h"

CallExpression::CallExpression(const std::string &name, const std::list<Expression *> &args)
    : name(name)
    , args(args) {
}

CallExpression::~CallExpression() {
    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Context *context) {
    Object *f = context->get(name);

    if (f == nullptr)
        Runtime::runtimeError("undefined identifier '" + name + "'");

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
