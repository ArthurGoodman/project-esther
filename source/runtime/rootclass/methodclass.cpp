#include "methodclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "interpretedblock.h"
#include "expression.h"

MethodClass::MethodClass()
    : RootClass("Method", "Function") {
}

Object *MethodClass::newInstance() {
    return new Method("", Runtime::getRoot(), {}, new InterpretedBlock(Expression::Empty()));
}

void MethodClass::setupMethods() {
}
