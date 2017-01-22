#include "interpretedfunction.h"

#include "runtime.h"

Object *InterpretedFunction::execute(Object *self, const std::vector<Object *> &args) {
    Context *childContext = context->childContext(self, context->getRuntime()->createObject());

    std::vector<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        childContext->setLocal(s, *i++);

    Object *value = body->eval(childContext);

    return value;
}

InterpretedFunction::InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context)
    : Function(objectClass, name, params.size())
    , params(params)
    , body(body)
    , context(context) {
}
