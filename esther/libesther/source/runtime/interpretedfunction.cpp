#include "interpretedfunction.h"

#include "esther.h"

int InterpretedFunction::getSize() const {
    return sizeof *this;
}

Pointer<Object> InterpretedFunction::execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    esther->pushContext(context->childContext(self, esther->createObject()));

    std::vector<Pointer<Object>>::const_iterator i = args.begin();
    for (const std::string &s : params)
        esther->context()->setLocal(s, *i++);

    Pointer<Object> value = body->eval(esther);

    esther->popContext();

    return value;
}

InterpretedFunction::InterpretedFunction(Pointer<Class> objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context)
    : Function(objectClass, name, params.size())
    , params(params)
    , body(body)
    , context(context) {
}
