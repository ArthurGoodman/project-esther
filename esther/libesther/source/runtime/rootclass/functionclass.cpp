#include "functionclass.h"

#include "nativefunction.h"
#include "interpretedfunction.h"
#include "esther.h"

Pointer<Function> FunctionClass::createNativeFunction(const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    return new NativeFunction(this, name, arity, body);
}

Pointer<Function> FunctionClass::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context) {
    return new InterpretedFunction(this, name, params, body, context);
}

Pointer<Object> FunctionClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}

void FunctionClass::setupMethods(Esther *esther) {
    defFunc(esther, "call", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (args.empty())
            Esther::runtimeError("Function.call: invalid number of arguments");

        Pointer<Object> actualSelf = args[0];

        std::vector<Pointer<Object>> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return ((Function *)*self)->invoke(esther, actualSelf, actualArgs);
    });

    setAttribute("()", getAttribute("call"));
}

FunctionClass::FunctionClass(Esther *esther)
    : RootClass(esther, "Function", esther->getObjectClass()) {
}
