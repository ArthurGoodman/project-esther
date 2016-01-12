#include "methodclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "interpretedblock.h"
#include "expression.h"
#include "signature.h"
#include "method.h"
#include "string.h"

MethodClass::MethodClass()
    : RootClass("Method", "Function") {
}

void MethodClass::setupMethods() {
    auto isStaticMethod = [](Object *self, Tuple *) -> Object *{
        return Runtime::toBoolean(((Method *)self)->isStatic());
    };

    setMethod("isStatic", new Signature("Boolean", {}), isStaticMethod);

    auto toStringMethod = [](Object *self, Tuple *) -> Object * {
        return new String(((Function *)self)->getName().empty() ? "<anonymous method>" : "<method " + ((Function *)self)->getName() + ">");
    };

    setMethod("toString", new Signature("String", {}), toStringMethod);
}

Object *MethodClass::createNewInstance() {
    return new Method("", Runtime::getRoot(), new Signature, new InterpretedBlock(Expression::Empty()), Runtime::getObjectClass());
}
