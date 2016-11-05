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

Object *FunctionClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Function class yet...");
    return nullptr;
}

FunctionClass::FunctionClass(Class *objectClass)
    : Class(objectClass, "Function", objectClass->getSuperclass()) {
}
