#include "characterclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "nativefunction.h"
#include "utility.h"

CharacterClass::CharacterClass(Esther *esther)
    : RootClass(esther, "Character", esther->getRootClass("Numeric")) {
}

void CharacterClass::setupMethods(Esther *esther) {
    setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                     if (!dynamic_cast<CharacterClass *>(*self)) {
                         Esther::runtimeError("Character.(): invalid self");
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *>(*args[1])) {
                         Esther::runtimeError("Character.(): invalid argument");
                         return nullptr;
                     }

                     return new ValueObject(esther, ((ValueObject *)*args[1])->getVariant().toChar());
                 }));

    defValueObjectFunc(esther, "initialize", -1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Character.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toChar());

        return self;
    });

    defFunc(esther, "isSpace", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return esther->toBoolean(Utility::isSpace(((ValueObject *)*self)->getVariant().toChar()));
    });

    defFunc(esther, "isDigit", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return esther->toBoolean(Utility::isDigit(((ValueObject *)*self)->getVariant().toChar()));
    });

    defFunc(esther, "isLetter", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return esther->toBoolean(Utility::isLetter(((ValueObject *)*self)->getVariant().toChar()));
    });

    defValueObjectFunc(esther, "=", 1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toChar());
        return self;
    });
}

void CharacterClass::copy(ManagedObject *dst) {
    new (dst) CharacterClass(*this);
}

Pointer<Object> CharacterClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new ValueObject(esther, '\0');
}
