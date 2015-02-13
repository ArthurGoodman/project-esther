#include "contextclass.h"

#include "runtime.h"
#include "context.h"

namespace esther {

ContextClass::ContextClass()
    : Class("Context") {
    Runtime::setRootClass(this);
}

Object *ContextClass::newInstance() {
    return new Context();
}

void ContextClass::setupMethods() {
}
}
