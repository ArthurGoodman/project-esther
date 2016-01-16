#include "characterclass.h"

#include "runtime.h"
#include "character.h"
#include "tuple.h"
#include "signature.h"
#include "utility.h"
#include "string.h"
#include "variant.h"
#include "method.h"

CharacterClass::CharacterClass()
    : RootClass("Character") {
}

void CharacterClass::setupMethods() {
    auto initMethod = [](Object *self, Tuple *) -> Object * {
        ((Character *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](Object *self, Tuple *args) -> Object * {
        ((Character *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toChar());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);

    setAttribute("=", getMethod("initialize"));

    auto plusMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toChar() + ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("+", new Signature("Character", {"Character"}), plusMethod);

    auto minusMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toChar() - ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("-", new Signature("Character", {"Character"}), minusMethod);

    auto unaryMinusMethod = [](Object *self, Tuple *) -> Object * {
        return new Character(-((ValueObject *)self)->getVariant().toChar());
    };

    setMethod("-", new Signature("Character", {}), unaryMinusMethod);

    auto multiplyMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toChar() * ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("*", new Signature("Character", {"Character"}), multiplyMethod);

    auto divideMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toChar() / ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("/", new Signature("Character", {"Character"}), divideMethod);

    auto modMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(((ValueObject *)self)->getVariant().toChar() % ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("%", new Signature("Character", {"Character"}), modMethod);

    auto powerMethod = [](Object *self, Tuple *args) -> Object * {
        return new Character(pow(((ValueObject *)self)->getVariant().toChar(), ((ValueObject *)args->at(0))->getVariant().toChar()));
    };

    setMethod("**", new Signature("Character", {"Character"}), powerMethod);

    auto ltMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() < ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("<", new Signature("Boolean", {"Character"}), ltMethod);

    auto gtMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() > ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod(">", new Signature("Boolean", {"Character"}), gtMethod);

    auto leMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() <= ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("<=", new Signature("Boolean", {"Character"}), leMethod);

    auto geMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() >= ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod(">=", new Signature("Boolean", {"Character"}), geMethod);

    auto incMethod = [](Object *self, Tuple *) -> Object * {
        ((Character *)self)->setValue(((ValueObject *)self)->getVariant().toChar() + 1);
        return self;
    };

    setMethod("++", new Signature("Character", {}), incMethod);

    auto decMethod = [](Object *self, Tuple *) -> Object * {
        ((Character *)self)->setValue(((ValueObject *)self)->getVariant().toChar() - 1);
        return self;
    };

    setMethod("--", new Signature("Character", {}), decMethod);

    auto isDigitMethod = [](Object *self, Tuple *) -> Object * {
        return Runtime::toBoolean(Utility::isDigit(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isDigit", new Signature("Boolean", {}), isDigitMethod);

    auto isLetterMethod = [](Object *self, Tuple *) -> Object * {
        return Runtime::toBoolean(Utility::isLetter(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isLetter", new Signature("Boolean", {}), isLetterMethod);

    auto isLetterOrDigitMethod = [](Object *self, Tuple *) -> Object * {
        return Runtime::toBoolean(Utility::isLetterOrDigit(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isLetterOrDigit", new Signature("Boolean", {}), isLetterOrDigitMethod);

    auto isSignMethod = [](Object *self, Tuple *) -> Object * {
        return Runtime::toBoolean(Utility::isSign(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isSign", new Signature("Boolean", {}), isSignMethod);

    auto isSpaceMethod = [](Object *self, Tuple *) -> Object * {
        return Runtime::toBoolean(Utility::isSpace(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isSpace", new Signature("Boolean", {}), isSpaceMethod);

    auto toLowerMethod = [](Object *self, Tuple *) -> Object * {
        return new Character(Utility::toLower(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("toLower", new Signature("Character", {}), toLowerMethod);

    auto toUpperMethod = [](Object *self, Tuple *) -> Object * {
        return new Character(Utility::toUpper(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("toUpper", new Signature("Character", {}), toUpperMethod);
}

Object *CharacterClass::createNewInstance() {
    return new Character;
}
