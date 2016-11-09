#include "callexpression.h"

#include "context.h"
#include "runtime.h"
#include "function.h"

CallExpression::CallExpression(Expression *self, Expression *name, const std::list<Expression *> &args)
    : self(self), name(name), args(args) {
}

CallExpression::~CallExpression() {
    delete self;
    delete name;

    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Context *context) {
    Object *evaledSelf = self ? self->eval(context) : nullptr;

    const std::string &name = this->name->eval(context)->toString();
    const std::pair<Object *, Object *> &f = context->getWithSource(name);

    if (!f.first)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    if (!evaledSelf)
        evaledSelf = f.second;

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    if (dynamic_cast<Function *>(f.first))
        return ((Function *)f.first)->invoke(evaledSelf, evaledArgs);

    evaledArgs.insert(evaledArgs.begin(), evaledSelf);

    return f.first->call("()", evaledArgs);
}
