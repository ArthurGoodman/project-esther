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
    auto initMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Character *)self)->setValue(0);
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initVariantMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Character *)self)->setValue(((ValueObject *)args->at(0))->getVariant().toChar());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Character"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Integer"}), initVariantMethod);
    setMethod("initialize", new Signature("Object", {"Float"}), initVariantMethod);

    setAttribute("=", getMethod("initialize"));

    auto plusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(((ValueObject *)self)->getVariant().toChar() + ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("+", new Signature("Character", {"Character"}), plusMethod);

    auto minusMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(((ValueObject *)self)->getVariant().toChar() - ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("-", new Signature("Character", {"Character"}), minusMethod);

    auto unaryMinusMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Character(-((ValueObject *)self)->getVariant().toChar());
    };

    setMethod("-", new Signature("Character", {}), unaryMinusMethod);

    auto multiplyMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(((ValueObject *)self)->getVariant().toChar() * ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("*", new Signature("Character", {"Character"}), multiplyMethod);

    auto divideMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(((ValueObject *)self)->getVariant().toChar() / ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("/", new Signature("Character", {"Character"}), divideMethod);

    auto modMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(((ValueObject *)self)->getVariant().toChar() % ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("%", new Signature("Character", {"Character"}), modMethod);

    auto powerMethod = [](IObject *self, Tuple *args) -> IObject * {
        return new Character(pow(((ValueObject *)self)->getVariant().toChar(), ((ValueObject *)args->at(0))->getVariant().toChar()));
    };

    setMethod("**", new Signature("Character", {"Character"}), powerMethod);

    auto ltMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() < ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("<", new Signature("Boolean", {"Character"}), ltMethod);

    auto gtMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() > ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod(">", new Signature("Boolean", {"Character"}), gtMethod);

    auto leMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() <= ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("<=", new Signature("Boolean", {"Character"}), leMethod);

    auto geMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() >= ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod(">=", new Signature("Boolean", {"Character"}), geMethod);

    auto incMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Character *)self)->setValue(((ValueObject *)self)->getVariant().toChar() + 1);
        return self;
    };

    setMethod("++", new Signature("Character", {}), incMethod);

    auto decMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Character *)self)->setValue(((ValueObject *)self)->getVariant().toChar() - 1);
        return self;
    };

    setMethod("--", new Signature("Character", {}), decMethod);

    auto isDigitMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(Utility::isDigit(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isDigit", new Signature("Boolean", {}), isDigitMethod);

    auto isLetterMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(Utility::isLetter(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isLetter", new Signature("Boolean", {}), isLetterMethod);

    auto isLetterOrDigitMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(Utility::isLetterOrDigit(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isLetterOrDigit", new Signature("Boolean", {}), isLetterOrDigitMethod);

    auto isSignMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(Utility::isSign(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isSign", new Signature("Boolean", {}), isSignMethod);

    auto isSpaceMethod = [](IObject *self, Tuple *) -> IObject * {
        return Runtime::toBoolean(Utility::isSpace(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("isSpace", new Signature("Boolean", {}), isSpaceMethod);

    auto toLowerMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Character(Utility::toLower(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("toLower", new Signature("Character", {}), toLowerMethod);

    auto toUpperMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Character(Utility::toUpper(((ValueObject *)self)->getVariant().toChar()));
    };

    setMethod("toUpper", new Signature("Character", {}), toUpperMethod);
}

IObject *CharacterClass::createNewInstance() {
    return new Character;
}
