#include "characterclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "numericclass.h"
#include "function.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance(const std::vector<Object *> &) {
    return createCharacter('\0');
}

void CharacterClass::setupMethods() {
    setAttribute("()", runtime->createNativeFunction("()", 2, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<CharacterClass *>(self)) {
            Runtime::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Runtime::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return runtime->createCharacter(((ValueObject *)args[1])->getVariant().toChar());
    }));
}

CharacterClass::CharacterClass(Runtime *runtime)
    : RootClass(runtime, "Character", runtime->getNumericClass()) {
}
