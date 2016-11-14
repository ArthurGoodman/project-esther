#include "interpretedfunction.h"

#include "runtime.h"

Object *InterpretedFunction::execute(Object *self, const std::vector<Object *> &args) {
    context->pushSelf(self);
    context->pushHere(context->getRuntime()->createObject());

    std::vector<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        context->setLocal(s, *i++);

    Object *value = body->eval(context);

    context->popSelf();
    context->popHere();

    return value;
}

InterpretedFunction::InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context)
    : Function(objectClass, name, params.size()), params(params), body(body), context(context) {
}
