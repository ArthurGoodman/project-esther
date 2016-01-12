#include "booleanclass.h"

#include "runtime.h"
#include "string.h"
#include "variant.h"
#include "signature.h"

BooleanClass::BooleanClass()
    : RootClass("Boolean") {
}

void BooleanClass::setupMethods() {
    auto toStringMethod = [](Object *self, Tuple *) -> Object *{
        return new String(self->isTrue() ? "true" : "false");
    };

    setMethod("toString", new Signature("String", {}), toStringMethod);
}

Object *BooleanClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return 0;
}
