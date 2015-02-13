#include "methodclass.h"

#include "runtime.h"
#include "method.h"
#include "nativemethod.h"

namespace esther {

MethodClass::MethodClass()
    : Class("Method", "Function") {
    Runtime::setRootClass(this);
}

Object *MethodClass::newInstance() {
    return new Method("", Runtime::getRoot(), {}, new NativeMethod([](Object *, Tuple *) -> Object * {
                          return Runtime::getNull();
                                                  }));
}

void MethodClass::setupMethods() {
}
}
