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
    auto initMethod = [](Object *self, Tuple *) -> Object *{
        ((String *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initCharacterMethod = [](Object *self, Tuple *args) -> Object *{
        ((String *)self)->setValue(string() + ((ValueObject *)args->at(0))->getVariant().toChar());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initCharacterMethod);

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

    auto emptyMethod = [](Object *self, Tuple *) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString().empty());
    };

    setMethod("empty", new Signature("Boolean", {}), emptyMethod);

    auto appendMethod = [](Object *self, Tuple *args) -> Object *{
        return new String(((ValueObject *)self)->getVariant().toString() + ((ValueObject *)args->at(0))->getVariant().toString());
    };

    setMethod("append", new Signature("String", {"String"}), appendMethod);
    setAttribute("+", getMethod("append"));

    auto plusAssignMethod = [](Object *self, Tuple *args) -> Object *{
        ((String *)self)->setValue(((ValueObject *)self)->getVariant().toString() + ((ValueObject *)args->at(0))->getVariant().toString());
        return self;
    };

    setMethod("+=", new Signature("String", {"String"}), plusAssignMethod);
}

Object *StringClass::createNewInstance() {
    return new String;
}
