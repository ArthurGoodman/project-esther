#include "stringclass.h"

#include "runtime.h"
#include "string.h"
#include "tuple.h"
#include "integer.h"
#include "character.h"
#include "signature.h"

StringClass::StringClass()
    : RootClass("String") {
}

Object *StringClass::newInstance() {
    return new String();
}

Object *StringClass::newInstance(Tuple *args) {
    return new String(args->at(0)->toString());
}

void StringClass::setupMethods() {
    auto sizeMethod = [](Object * self, Tuple *) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toString().size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](Object * self, Tuple * args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toString().at(((Integer *)args->at(0))->getVariant().toInteger()));
    };

    setMethod("at", new Signature("Character", {"Integer"}), atMethod);

    auto equalsMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString() == ((ValueObject *)args->at(0))->getVariant().toString());
    };

    setMethod("equals", new Signature("Boolean", {"String"}), equalsMethod);
}
