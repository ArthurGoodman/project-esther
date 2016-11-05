#include "interpretedfunction.h"

Object *InterpretedFunction::execute(Object *self, const std::list<Object *> &args) {
    context->setSelf(self);
    context->clear();

    std::list<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        context->setLocal(s, *i++);

    return body->eval(context);
}

InterpretedFunction::InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context)
    : Function(objectClass, name, params.size()), params(params), body(body), context(context) {
}
