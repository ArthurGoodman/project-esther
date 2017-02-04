#include "runtime/rootclass/functionclass.h"

#include "runtime/nativefunction.h"
#include "runtime/interpretedfunction.h"
#include "esther.h"

namespace es {

FunctionClass::FunctionClass(Esther *esther)
    : RootClass(esther, "Function", esther->getObjectClass()) {
}

void FunctionClass::setupMethods(Esther *esther) {
    Ptr<FunctionClass> _this = this;

    _this->defFunc(esther, "call", -1, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        if (args.empty())
            Esther::runtimeError("Function.call: invalid number of arguments");

        Ptr<Object> actualSelf = args[0];

        std::vector<Ptr<Object>> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return static_cast<Function *>(*self)->invoke(esther, actualSelf, actualArgs);
    });

    _this->setAttribute(esther, "()", _this->getAttribute(esther, "call"));
}

Ptr<Object> FunctionClass::createNewInstance(Esther *, const std::vector<Ptr<Object>> &) {
    Esther::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}
}
