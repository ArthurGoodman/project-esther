#include "callexpression.h"

#include "context.h"
#include "runtime.h"
#include "function.h"

CallExpression::CallExpression(Expression *name, const std::list<Expression *> &args)
    : name(name), args(args) {
}

CallExpression::~CallExpression() {
    delete name;

    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Context *context) {
    std::string name = this->name->eval(context)->toString();
    std::pair<Object *, Object *> f = context->getWithSource(name);

    if (!f.first)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    if (dynamic_cast<Function *>(f.first))
        return ((Function *)f.first)->invoke(f.second, evaledArgs);

    evaledArgs.insert(evaledArgs.begin(), f.second);

    return f.first->call("()", evaledArgs);
}
