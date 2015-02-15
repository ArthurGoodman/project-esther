#include "functionclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "tuple.h"

FunctionClass::FunctionClass()
    : Class("Function") {
    Runtime::setRootClass(this);
}

Object *FunctionClass::newInstance() {
    auto body = [](Object *, Tuple *) -> Object * {
        return Runtime::getNull();
    };

    return new Function("", Runtime::getRoot(), {}, new NativeBlock(body));
}

void FunctionClass::setupMethods() {
    auto parenthesesMethod = [](Object * self, Tuple * args) -> Object * {
        list<Object *> argsList;

        for (int i = 1; i < args->size(); i++)
            argsList << args->at(i);

        Object *value = ((Function *)self)->invoke(args->at(0), new Tuple(argsList));
        return value;
    };

    setMethod("()", parenthesesMethod);
}
