#include "integerclass.h"

#include <cmath>

#include "runtime.h"
#include "integer.h"
#include "tuple.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "signature.h"
#include "string.h"
#include "valueobject.h"
#include "range.h"

IntegerClass::IntegerClass()
    : RootClass("Integer") {
}

void IntegerClass::setupMethods() {
    auto initMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Integer *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Integer *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toInteger());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"String"}), initVariantMethod);

    setAttribute("=", getMethod("initialize"));

    auto plusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() + ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("+", new Signature("Integer", {"Integer"}), plusMethod);

    auto minusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() - ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("-", new Signature("Integer", {"Integer"}), minusMethod);

    auto unaryMinusMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Integer(-((ValueObject *)self)->getVariant().toInteger());
    };

    setMethod("-", new Signature("Integer", {}), unaryMinusMethod);

    auto multiplyMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() * ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("*", new Signature("Integer", {"Integer"}), multiplyMethod);

    auto divideMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() / ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("/", new Signature("Integer", {"Integer"}), divideMethod);

    auto modMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() % ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("%", new Signature("Integer", {"Integer"}), modMethod);

    auto powerMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Integer(pow(((ValueObject *)self)->getVariant().toInteger(), ((ValueObject *)args->at(0))->getVariant().toInteger()));
    };

    setMethod("**", new Signature("Integer", {"Integer"}), powerMethod);

    auto ltMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() < ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("<", new Signature("Boolean", {"Integer"}), ltMethod);

    auto gtMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() > ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod(">", new Signature("Boolean", {"Integer"}), gtMethod);

    auto leMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() <= ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("<=", new Signature("Boolean", {"Integer"}), leMethod);

    auto geMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() >= ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod(">=", new Signature("Boolean", {"Integer"}), geMethod);

    auto incMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Integer *)self)->setValue(((ValueObject *)self)->getVariant().toInteger() + 1);
        return self;
    };

    setMethod("++", new Signature("Integer", {}), incMethod);

    auto decMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Integer *)self)->setValue(((ValueObject *)self)->getVariant().toInteger() - 1);
        return self;
    };

    setMethod("--", new Signature("Integer", {}), decMethod);

    auto plusAssignMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Integer *)self)->setValue(((ValueObject *)self)->getVariant().toInteger() + ((ValueObject *)args->at(0))->getVariant().toInteger());
        return self;
    };

    setMethod("+=", new Signature("Integer", {"Integer"}), plusAssignMethod);

    auto rangeMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Range(((Integer *)self)->getVariant().toInteger(), ((Integer *)args->at(0))->getVariant().toInteger());
    };

    setMethod("..", new Signature("Range", {"Integer"}), rangeMethod);
}

IObject *IntegerClass::createNewInstance() {
    return new Integer;
}
