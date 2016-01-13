#include "stringclass.h"

#include "runtime.h"
#include "string.h"
#include "tuple.h"
#include "integer.h"
#include "character.h"
#include "signature.h"
#include "method.h"
#include "outofrangeexception.h"
#include "runtimeerror.h"
#include "io.h"
#include "utility.h"

StringClass::StringClass()
    : RootClass("String") {
}

void StringClass::setupMethods() {
    auto initMethod = [](Object *self, Tuple *) -> Object *{
        ((String *)self)->setValue("");
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](Object *self, Tuple *args) -> Object *{
        ((String *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toString());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"String"}), initVariantMethod);

    auto sizeMethod = [](Object *self, Tuple *) -> Object *{
        return new Integer(((ValueObject *)self)->getVariant().toString().size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](Object *self, Tuple *args) -> Object *{
        string str = ((ValueObject *)self)->getVariant().toString();
        int index = ((Integer *)args->at(0))->getVariant().toInteger();

        if (index >= (int)str.size())
            throw new OutOfRangeException;

        return new Character(str.at(index));
    };

    setMethod("at", new Signature("Character", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));

    auto emptyMethod = [](Object *self, Tuple *) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString().empty());
    };

    setMethod("empty", new Signature("Boolean", {}), emptyMethod);

    auto containsMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString().find(((ValueObject *)args->at(0))->getVariant().toChar()) != string::npos);
    };

    setMethod("contains", new Signature("Boolean", {"Character"}), containsMethod);

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
