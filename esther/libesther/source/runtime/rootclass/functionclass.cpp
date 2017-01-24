#include "functionclass.h"

#include "nativefunction.h"
#include "interpretedfunction.h"
#include "runtime.h"

Function *FunctionClass::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    return new NativeFunction(this, name, arity, body);
}

Function *FunctionClass::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return new InterpretedFunction(this, name, params, body, context);
}

Object *FunctionClass::createNewInstance(const std::vector<Object *> &) {
    Runtime::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}

void FunctionClass::setupMethods() {
    defFunc("call", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (args.empty())
            Runtime::runtimeError(getName() + ".call: invalid number of arguments");

        Object *actualSelf = args[0];

        std::vector<Object *> actualArgs = args;
        actualArgs.erase(actualArgs.begin());

        return ((Function *)self)->invoke(actualSelf, actualArgs);
    });

    setAttribute("()", getAttribute("call"));
}

FunctionClass::FunctionClass(Runtime *runtime)
    : RootClass(runtime, "Function", runtime->getObjectClass()) {
}
