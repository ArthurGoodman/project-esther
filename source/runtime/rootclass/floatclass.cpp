#include "floatclass.h"

#include "runtime.h"
#include "float.h"
#include "tuple.h"
#include "signature.h"
#include "string.h"
#include "variant.h"
#include "method.h"

FloatClass::FloatClass()
    : RootClass("Float") {
}

void FloatClass::setupMethods() {
    auto initMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Float *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Float *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toFloat());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"String"}), initVariantMethod);

    setAttribute("=", getMethod("initialize"));

    auto plusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(((ValueObject *)self)->getVariant().toFloat() + ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("+", new Signature("Float", {"Float"}), plusMethod);

    auto minusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(((ValueObject *)self)->getVariant().toFloat() - ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("-", new Signature("Float", {"Float"}), minusMethod);

    auto unaryMinusMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Float(-((ValueObject *)self)->getVariant().toFloat());
    };

    setMethod("-", new Signature("Float", {}), unaryMinusMethod);

    auto multiplyMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(((ValueObject *)self)->getVariant().toFloat() * ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("*", new Signature("Float", {"Float"}), multiplyMethod);

    auto divideMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(((ValueObject *)self)->getVariant().toFloat() / ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("/", new Signature("Float", {"Float"}), divideMethod);

    auto modMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(fmod(((ValueObject *)self)->getVariant().toFloat(), ((ValueObject *)args->at(0))->getVariant().toFloat()));
    };

    setMethod("%", new Signature("Float", {"Float"}), modMethod);

    auto powerMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Float(pow(((ValueObject *)self)->getVariant().toFloat(), ((ValueObject *)args->at(0))->getVariant().toFloat()));
    };

    setMethod("**", new Signature("Float", {"Float"}), powerMethod);

    auto ltMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() < ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("<", new Signature("Boolean", {"Float"}), ltMethod);

    auto gtMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() >= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod(">", new Signature("Boolean", {"Float"}), gtMethod);

    auto leMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() <= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("<=", new Signature("Boolean", {"Float"}), leMethod);

    auto geMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() >= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod(">=", new Signature("Boolean", {"Float"}), geMethod);

    auto incMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Float *)self)->setValue(((Float *)self)->getVariant().toFloat() + 1);
        return self;
    };

    setMethod("++", new Signature("Float", {}), incMethod);

    auto decMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Float *)self)->setValue(((Float *)self)->getVariant().toFloat() - 1);
        return self;
    };

    setMethod("--", new Signature("Float", {}), decMethod);

    auto plusAssignMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Float *)self)->setValue(((ValueObject *)self)->getVariant().toFloat() + ((ValueObject *)args->at(0))->getVariant().toFloat());
        return self;
    };

    setMethod("+=", new Signature("Float", {"Float"}), plusAssignMethod);
}

IObject *FloatClass::createNewInstance() {
    return new Float;
}
