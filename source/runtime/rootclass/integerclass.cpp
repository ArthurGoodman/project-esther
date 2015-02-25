#include "integerclass.h"

#include "runtime.h"
#include "integer.h"
#include "tuple.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "signature.h"

IntegerClass::IntegerClass()
    : RootClass("Integer") {
}

Object *IntegerClass::newInstance() {
    return new Integer;
}

void IntegerClass::setupMethods() {
    auto plusMethod = [](Object * self, Tuple * args) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() + ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("+", new Signature("Integer", {"Integer"}), plusMethod);

    auto equalsMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() == ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("equals", new Signature("Boolean", {"Integer"}), equalsMethod);
}
