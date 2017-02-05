#include "runtime/rootclass/characterclass.h"

#include "runtime/valueobject.h"
#include "esther.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/nativefunction.h"
#include "common/utility.h"

namespace es {

CharacterClass::CharacterClass(Esther *esther)
    : RootClass(esther, "Character", esther->getRootClass("Numeric")) {
}

void CharacterClass::setupMethods(Esther *esther) {
    setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
                     if (!dynamic_cast<CharacterClass *>(self)) {
                         Esther::runtimeError("Character.(): invalid self");
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *>(args[1])) {
                         Esther::runtimeError("Character.(): invalid argument");
                         return nullptr;
                     }

                     return new ValueObject(esther, (static_cast<ValueObject *>(args[1]))->getVariant().toChar());
                 }));

    defValueObjectFunc(esther, "initialize", -1, [](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if (static_cast<int>(args.size()) > 1)
            Esther::runtimeError("Character.initialize: invalid number of arguments");

        if (!args.empty())
            static_cast<ValueObject *>(self)->setVariant(static_cast<ValueObject *>(args[0])->getVariant().toChar());

        return self;
    });

    defFunc(esther, "isSpace", [](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isSpace(static_cast<ValueObject *>(self)->getVariant().toChar()));
    });

    defFunc(esther, "isDigit", [](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isDigit(static_cast<ValueObject *>(self)->getVariant().toChar()));
    });

    defFunc(esther, "isLetter", [](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->toBoolean(Utility::isLetter(static_cast<ValueObject *>(self)->getVariant().toChar()));
    });

    defValueObjectFunc(esther, "=", 1, [](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        static_cast<ValueObject *>(self)->setVariant(static_cast<ValueObject *>(args[0])->getVariant().toChar());
        return self;
    });
}

Object *CharacterClass::createNewInstance(Esther *esther, const std::vector<Object *> &) {
    return new ValueObject(esther, '\0');
}
}
