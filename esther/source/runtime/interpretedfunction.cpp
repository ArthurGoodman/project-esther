#include "interpretedfunction.h"

InterpretedFunction::InterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body)
    : Function(name, params.size()), params(params), body(body), context(0) {
}

void InterpretedFunction::setContext(Context *context) {
    this->context = context;
}

Object *InterpretedFunction::execute(Object *self, const std::list<Object *> &args) {
    context->setSelf(self);
    context->clear();

    std::list<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        context->setLocal(s, *i++);

    return body->eval(context);
}
