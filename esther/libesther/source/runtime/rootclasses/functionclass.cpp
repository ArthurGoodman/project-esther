#include "functionclass.h"

#include "nativefunction.h"
#include "interpretedfunction.h"

Function *FunctionClass::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body) {
    return new NativeFunction(this, name, arity, body);
}

Function *FunctionClass::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return new InterpretedFunction(this, name, params, body, context);
}

FunctionClass::FunctionClass(Class *objectClass)
    : Class(objectClass, "Function", objectClass->getSuperclass()) {
}
