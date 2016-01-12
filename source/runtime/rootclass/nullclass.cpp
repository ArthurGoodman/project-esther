#include "nullclass.h"

#include "runtime.h"
#include "signature.h"
#include "string.h"

NullClass::NullClass()
    : RootClass("Null") {
}

void NullClass::setupMethods() {
    auto toStringMethod = [](Object *, Tuple *) -> Object * {
        return new String("null");
    };

    setMethod("toString", new Signature("String", {}), toStringMethod);
}

Object *NullClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return 0;
}
