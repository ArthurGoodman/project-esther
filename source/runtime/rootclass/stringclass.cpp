#include "stringclass.h"

#include "runtime.h"
#include "string.h"
#include "tuple.h"
#include "integer.h"
#include "character.h"
#include "signature.h"
#include "method.h"

StringClass::StringClass()
    : RootClass("String") {
}

void StringClass::setupMethods() {
    auto sizeMethod = [](Object *self, Tuple *) -> Object *{
        return new Integer(((ValueObject *)self)->getVariant().toString().size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](Object *self, Tuple *args) -> Object *{
        return new Character(((ValueObject *)self)->getVariant().toString().at(((Integer *)args->at(0))->getVariant().toInteger()));
    };

    setMethod("at", new Signature("Character", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));

    auto equalsMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString() == ((ValueObject *)args->at(0))->getVariant().toString());
    };

    setMethod("equals", new Signature("Boolean", {"String"}), equalsMethod);
}

Object *StringClass::createNewInstance() {
    return new String;
}
