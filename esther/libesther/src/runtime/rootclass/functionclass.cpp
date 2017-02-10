#include "runtime/rootclass/functionclass.h"

#include "esther.h"
#include "runtime/nativefunction.h"
#include "runtime/interpretedfunction.h"

namespace es {

FunctionClass::FunctionClass(Esther *esther)
    : RootClass(esther, "Function", esther->getObjectClass()) {
}

void FunctionClass::setupMethods(Esther *esther) {
    defFunc(esther, "call", -1, [](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
        if (args.empty())
            Esther::runtimeError("Function.call: invalid number of arguments");

        Object *volatile actualSelf = args[0];

        std::vector<Object *> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return static_cast<Function *volatile>(self)->invoke(esther, actualSelf, actualArgs);
    });

    setAttribute("()", getAttribute("call"));
}

Object *FunctionClass::createNewInstance(Esther *, const std::vector<Object *> &) {
    Esther::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}
}
