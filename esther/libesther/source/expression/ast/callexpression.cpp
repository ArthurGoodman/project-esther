#include "callexpression.h"

#include "context.h"
#include "runtime.h"
#include "function.h"

CallExpression::CallExpression(const std::string &name, const std::list<Expression *> &args)
    : name(name), args(args) {
}

CallExpression::~CallExpression() {
    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Context *context) {
    const std::pair<Object *, Object *> &f = context->getWithSource(name);

    if (!f.first)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    if (dynamic_cast<Function *>(f.first)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return ((Function *)f.first)->invoke(f.second, evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << f.second;

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return f.first->call("()", evaledArgs);
    }
}
