#include "floatclass.h"

#include "runtime.h"
#include "float.h"
#include "tuple.h"
#include "signature.h"
#include "string.h"
#include "variant.h"

FloatClass::FloatClass()
    : RootClass("Float") {
}

void FloatClass::setupMethods() {
    auto initMethod = [](Object *self, Tuple *) -> Object *{
        ((Float *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](Object *self, Tuple *args) -> Object *{
        ((Float *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toFloat());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"String"}), initVariantMethod);

    auto plusMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(((ValueObject *)self)->getVariant().toFloat() + ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("+", new Signature("Float", {"Float"}), plusMethod);

    auto minusMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(((ValueObject *)self)->getVariant().toFloat() - ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("-", new Signature("Float", {"Float"}), minusMethod);

    auto multiplyMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(((ValueObject *)self)->getVariant().toFloat() * ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("*", new Signature("Float", {"Float"}), multiplyMethod);

    auto divideMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(((ValueObject *)self)->getVariant().toFloat() / ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("/", new Signature("Float", {"Float"}), divideMethod);

    auto modMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(fmod(((ValueObject *)self)->getVariant().toFloat(), ((ValueObject *)args->at(0))->getVariant().toFloat()));
    };

    setMethod("%", new Signature("Float", {"Float"}), modMethod);

    auto powerMethod = [](Object *self, Tuple *args) -> Object *{
        return new Float(pow(((ValueObject *)self)->getVariant().toFloat(), ((ValueObject *)args->at(0))->getVariant().toFloat()));
    };

    setMethod("**", new Signature("Float", {"Float"}), powerMethod);

    auto ltMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() < ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("<", new Signature("Boolean", {"Float"}), ltMethod);

    auto gtMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() >= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod(">", new Signature("Boolean", {"Float"}), gtMethod);

    auto leMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() <= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod("<=", new Signature("Boolean", {"Float"}), leMethod);

    auto geMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toFloat() >= ((ValueObject *)args->at(0))->getVariant().toFloat());
    };

    setMethod(">=", new Signature("Boolean", {"Float"}), geMethod);

    auto incMethod = [](Object *self, Tuple *) -> Object *{
        ((Float *)self)->setValue(((Float *)self)->getVariant().toFloat() + 1);
        return self;
    };

    setMethod("++", new Signature("Float", {}), incMethod);

    auto decMethod = [](Object *self, Tuple *) -> Object *{
        ((Float *)self)->setValue(((Float *)self)->getVariant().toFloat() - 1);
        return self;
    };

    setMethod("--", new Signature("Float", {}), decMethod);
}

Object *FloatClass::createNewInstance() {
    return new Float;
}
