#include "contextclass.h"

#include "runtime.h"
#include "context.h"

ContextClass::ContextClass()
    : RootClass("Context") {
}

Object *ContextClass::newInstance() {
    return new Context;
}

void ContextClass::setupMethods() {
}
