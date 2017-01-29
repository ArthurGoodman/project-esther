#include "functionclass.h"

#include "nativefunction.h"
#include "interpretedfunction.h"
#include "esther.h"

Function *FunctionClass::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    return new NativeFunction(this, name, arity, body);
}

Function *FunctionClass::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return new InterpretedFunction(this, name, params, body, context);
}

Object *FunctionClass::createNewInstance(const std::vector<Object *> &) {
    Esther::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}

void FunctionClass::setupMethods(Esther *esther) {
    defFunc(esther, "call", -1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (args.empty())
            Esther::runtimeError(getName() + ".call: invalid number of arguments");

        Object *actualSelf = args[0];

        std::vector<Object *> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return ((Function *)self)->invoke(esther, actualSelf, actualArgs);
    });

    setAttribute("()", getAttribute("call"));
}

FunctionClass::FunctionClass(Esther *esther)
    : RootClass(esther, "Function", esther->getObjectClass()) {
}
