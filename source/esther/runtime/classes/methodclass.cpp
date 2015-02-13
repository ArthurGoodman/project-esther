#include "methodclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"

namespace esther {

MethodClass::MethodClass()
    : Class("Method", "Function") {
    Runtime::setRootClass(this);
}

Object *MethodClass::newInstance() {
    auto body = [](Object *, Tuple *) -> Object * {
        return Runtime::getNull();
    };

    return new Method("", Runtime::getRoot(), {}, new NativeBlock(body));
}

void MethodClass::setupMethods() {
}
}
