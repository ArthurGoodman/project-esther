#include "nativefunction.h"

#include "esther.h"

NativeFunction::NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body)
    : Function(esther->getRootClass("Function"), name, arity)
    , body(new FunctionBody(body)) {
}

NativeFunction::~NativeFunction() {
    delete body;
}

int NativeFunction::getSize() const {
    return sizeof *this;
}

Ptr<Object> NativeFunction::execute(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) {
    Ptr<NativeFunction> _this = this;

    return (*_this->body)(esther, self, args);
}
