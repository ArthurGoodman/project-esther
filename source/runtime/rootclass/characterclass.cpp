#include "characterclass.h"

#include "runtime.h"
#include "character.h"
#include "tuple.h"
#include "signature.h"

CharacterClass::CharacterClass()
    : RootClass("Character") {
}

void CharacterClass::setupMethods() {
    auto equalsMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((ValueObject *)self)->getVariant().toChar() == ((ValueObject *)args->at(0))->getVariant().toChar());
    };

    setMethod("equals", new Signature("Boolean", {"Character"}), equalsMethod);
}

Object *CharacterClass::createNewInstance() {
    return new Character;
}
