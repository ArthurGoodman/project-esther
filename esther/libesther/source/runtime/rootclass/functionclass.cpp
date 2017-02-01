#include "functionclass.h"

#include "nativefunction.h"
#include "interpretedfunction.h"
#include "esther.h"

FunctionClass::FunctionClass(Esther *esther)
    : RootClass(esther, "Function", esther->getObjectClass()) {
}

void FunctionClass::setupMethods(Esther *esther) {
    Pointer<FunctionClass> _this = this;

    _this->defFunc(esther, "call", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (args.empty())
            Esther::runtimeError("Function.call: invalid number of arguments");

        Pointer<Object> actualSelf = args[0];

        std::vector<Pointer<Object>> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return ((Function *)*self)->invoke(esther, actualSelf, actualArgs);
    });

    _this->setAttribute("()", _this->getAttribute("call"));
}

void FunctionClass::copy(ManagedObject *dst) {
    new (dst) FunctionClass(*this);
}

Pointer<Object> FunctionClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}
