#include "runtime/interpretedfunction.h"

#include "esther.h"

namespace es {

InterpretedFunction::InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context)
    : Function(esther->getRootClass("Function"), name, params.size())
    , params(params)
    , body(body)
    , context(context) {
}

void InterpretedFunction::finalize() {
    Function::finalize();

    params.~list();
}

void InterpretedFunction::mapOnReferences(void (*f)(ManagedObject *&)) {
    Function::mapOnReferences(f);

    f(reinterpret_cast<ManagedObject *&>(context));
}

Object *InterpretedFunction::execute(Esther *esther, Object *self, const std::vector<Object *> &args) {
    esther->pushContext(context->childContext(self, esther->createObject()));

    std::vector<Object *>::const_iterator i = args.begin();
    for (const std::string &s : params)
        esther->context()->setLocal(s, *i++);

    Object *value = body->eval(esther);

    esther->popContext();

    return value;
}
}
