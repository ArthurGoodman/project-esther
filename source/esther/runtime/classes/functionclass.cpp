#include "functionclass.h"

#include "runtime.h"
#include "function.h"
#include "callstack.h"
#include "call.h"
#include "function.h"
#include "context.h"
#include "nativemethod.h"
#include "method.h"

namespace esther {

FunctionClass::FunctionClass()
    : Class("Function") {
    Runtime::setRootClass(this);
}

Object *FunctionClass::newInstance() {
    return new Function("", Runtime::getRoot(), {}, new NativeMethod([](Object *, Tuple *) -> Object * {
                            return Runtime::getNull();
                                                    }));
}

void FunctionClass::setupMethods() {
    auto parenthesesMethod = [](Object * self, Tuple * args) -> Object * {
        Runtime::beginCall(new Call(Runtime::getCallStack()->current()->getContext(), args));
        Object *value = ((Function *)self)->invoke(Runtime::getCallStack()->current()->getContext()->getCurrentSelf(), args);
        Runtime::endCall();
        return value;
    };

    setMethod(new Method("()", Runtime::getRoot(), {"args"}, new NativeMethod(parenthesesMethod)));
}
}
