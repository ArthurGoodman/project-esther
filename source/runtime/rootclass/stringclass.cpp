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
    auto initMethod = [](IObject *self, Tuple *) -> IObject * {
        ((String *)self)->setValue("");
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((String *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toString());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"String"}), initVariantMethod);

    setAttribute("=", getMethod("initialize"));

    auto sizeMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toString().size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](IObject *self, Tuple *args) -> IObject * {
        string str = ((ValueObject *)self)->getVariant().toString();
        int index = ((Integer *)args->at(0))->getVariant().toInteger();

        if (index >= (int)str.size())
            throw new OutOfRangeException;

        return new Character(str.at(index));
    };

    setMethod("at", new Signature("Character", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));

    auto emptyMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString().empty());
    };

    setMethod("empty", new Signature("Boolean", {}), emptyMethod);

    auto containsMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toString().find(((ValueObject *)args->at(0))->getVariant().toChar()) != string::npos);
    };

    setMethod("contains", new Signature("Boolean", {"Character"}), containsMethod);

    auto appendMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new String(((ValueObject *)self)->getVariant().toString() + ((ValueObject *)args->at(0))->getVariant().toString());
    };

    setMethod("append", new Signature("String", {"String"}), appendMethod);
    setAttribute("+", getMethod("append"));

    auto plusAssignMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((String *)self)->setValue(((ValueObject *)self)->getVariant().toString() + ((ValueObject *)args->at(0))->getVariant().toString());
        return self;
    };

    setMethod("+=", new Signature("String", {"String"}), plusAssignMethod);

    auto capitalizeMethod = [](IObject *self, Tuple *) -> IObject * {
        string value = ((String *)self)->getVariant().toString();

        if (value.empty())
            return self;

        value[0] = toupper(value[0]);

        return new String(value);
    };

    setMethod("capitalize", new Signature("String", {}), capitalizeMethod);
}

IObject *StringClass::createNewInstance() {
    return new String;
}
