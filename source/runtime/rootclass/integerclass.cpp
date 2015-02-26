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

    auto minusMethod = [](Object * self, Tuple * args) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() - ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("-", new Signature("Integer", {"Integer"}), minusMethod);

    auto multiplyMethod = [](Object * self, Tuple * args) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() * ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("*", new Signature("Integer", {"Integer"}), multiplyMethod);

    auto divideMethod = [](Object * self, Tuple * args) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() / ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("/", new Signature("Integer", {"Integer"}), divideMethod);

    auto modMethod = [](Object * self, Tuple * args) -> Object * {
        return new Integer(((ValueObject *)self)->getVariant().toInteger() % ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("%", new Signature("Integer", {"Integer"}), modMethod);

    auto ltMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() < ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("<", new Signature("Boolean", {"Integer"}), ltMethod);

    auto gtMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() > ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod(">", new Signature("Boolean", {"Integer"}), gtMethod);

    auto leMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() <= ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("<=", new Signature("Boolean", {"Integer"}), leMethod);

    auto geMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() >= ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod(">=", new Signature("Boolean", {"Integer"}), geMethod);

    auto incMethod = [](Object * self, Tuple *) -> Object * {
        ((Integer *)self)->setValue(((Integer *)self)->getVariant().toInteger() + 1);
        return self;
    };

    setMethod("++", new Signature("Integer", {}), incMethod);

    auto decMethod = [](Object * self, Tuple *) -> Object * {
        ((Integer *)self)->setValue(((Integer *)self)->getVariant().toInteger() - 1);
        return self;
    };

    setMethod("--", new Signature("Integer", {}), decMethod);

    auto equalsMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toInteger() == ((ValueObject *)args->at(0))->getVariant().toInteger());
    };

    setMethod("equals", new Signature("Boolean", {"Integer"}), equalsMethod);
}
