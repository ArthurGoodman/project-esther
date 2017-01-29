#include "interpretedfunction.h"

#include "esther.h"

Object *InterpretedFunction::execute(Esther *esther, Object *self, const std::vector<Object *> &args) {
    esther->pushContext(context->childContext(self, esther->createObject()));

    std::vector<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        esther->context()->setLocal(s, *i++);

    Object *value = body->eval(esther);

    esther->popContext();

    return value;
}

InterpretedFunction::InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context)
    : Function(objectClass, name, params.size())
    , params(params)
    , body(body)
    , context(context) {
}
