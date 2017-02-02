#include "interpretedfunction.h"

#include "runtime/esther.h"

InterpretedFunction::InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Ptr<Context> context)
    : Function(esther->getRootClass("Function"), name, params.size())
    , params(new std::list<std::string>(params))
    , body(body)
    , context(context) {
}

void InterpretedFunction::finalize() {
    Function::finalize();

    delete params;
}

void InterpretedFunction::mapOnReferences(const std::function<void(ManagedObject *&)> &f) {
    f(reinterpret_cast<ManagedObject *&>(context));
}

int InterpretedFunction::getSize() const {
    return sizeof *this;
}

Ptr<Object> InterpretedFunction::execute(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) {
    Ptr<InterpretedFunction> _this = this;

    esther->pushContext(_this->context->childContext(self, esther->createObject()));

    std::vector<Ptr<Object>>::const_iterator i = args.begin();
    for (const std::string &s : *_this->params)
        esther->context()->setLocal(s, *i++);

    Ptr<Object> value = _this->body->eval(esther);

    esther->popContext();

    return value;
}
