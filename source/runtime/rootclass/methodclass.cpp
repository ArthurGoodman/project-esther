#include "methodclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "interpretedblock.h"
#include "expression.h"
#include "signature.h"

MethodClass::MethodClass()
    : RootClass("Method", "Function") {
}

Object *MethodClass::newInstance() {
    return new Method("", Runtime::getRoot(), new Signature, new InterpretedBlock(Expression::Empty()));
}

void MethodClass::setupMethods() {
}
