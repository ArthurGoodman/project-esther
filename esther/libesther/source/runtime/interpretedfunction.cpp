#include "interpretedfunction.h"

#include "esther.h"

InterpretedFunction::InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context)
    : Function(esther->getRootClass("Function"), name, params.size())
    , params(params)
    , body(body)
    , context(context) {
}

void InterpretedFunction::copy(ManagedObject *dst) {
    new (dst) InterpretedFunction(*this);
}

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
