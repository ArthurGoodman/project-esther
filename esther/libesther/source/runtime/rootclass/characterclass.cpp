#include "characterclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "function.h"
#include "utility.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance(const std::vector<Object *> &) {
    return createCharacter('\0');
}

void CharacterClass::setupMethods() {
    setAttribute("()", esther->createNativeFunction("()", 2, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<CharacterClass *>(self)) {
            Esther::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Esther::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return esther->createCharacter(((ValueObject *)args[1])->getVariant().toChar());
    }));

    defValueObjectFunc("initialize", -1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toChar());

        return self;
    });

    defFunc("isSpace", [=](Esther *, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isSpace(((ValueObject *)self)->getVariant().toChar()));
    });

    defFunc("isDigit", [=](Esther *, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isDigit(((ValueObject *)self)->getVariant().toChar()));
    });

    defFunc("isLetter", [=](Esther *, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isLetter(((ValueObject *)self)->getVariant().toChar()));
    });

    defValueObjectFunc("=", 1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toChar());
        return self;
    });
}

CharacterClass::CharacterClass(Esther *e)
    : RootClass(e, "Character", e->getNumericClass()) {
}
