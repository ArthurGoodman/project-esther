#include "interpretedfunction.h"

#include "esther.h"

InterpretedFunction::InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context)
    : Function(esther->getRootClass("Function"), name, params.size())
    , params(new std::list<std::string>(params))
    , body(body)
    , context(context) {
}

InterpretedFunction::~InterpretedFunction() {
    delete params;
}

void InterpretedFunction::mapOnReferences(const std::function<void(ManagedObject *&)> &f) {
    f((ManagedObject *&)context);
}

int InterpretedFunction::getSize() const {
    return sizeof *this;
}

Pointer<Object> InterpretedFunction::execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    Pointer<InterpretedFunction> _this = this;

    esther->pushContext(_this->context->childContext(self, esther->createObject()));

    std::vector<Pointer<Object>>::const_iterator i = args.begin();
    for (const std::string &s : *_this->params)
        esther->context()->setLocal(s, *i++);

    Pointer<Object> value = _this->body->eval(esther);

    esther->popContext();

    return value;
}
