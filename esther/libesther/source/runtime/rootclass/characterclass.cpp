#include "characterclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance(const std::vector<Object *> &) {
    return createCharacter('\0');
}

void CharacterClass::setupMethods() {
    def("+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toChar() + b.toChar();
    });

    def("-", [](const Variant &a, const Variant &b) -> Variant {
        return a.toChar() - b.toChar();
    });

    def("*", [](const Variant &a, const Variant &b) -> Variant {
        return a.toChar() * b.toChar();
    });

    def("/", [](const Variant &a, const Variant &b) -> Variant {
        return a.toChar() / b.toChar();
    });

    def("%", [](const Variant &a, const Variant &b) -> Variant {
        return a.toChar() % b.toChar();
    });

    def("<", [](const Variant &a, const Variant &b) -> bool {
        return a.toChar() < b.toChar();
    });

    def("<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toChar() <= b.toChar();
    });

    def(">", [](const Variant &a, const Variant &b) -> bool {
        return a.toChar() > b.toChar();
    });

    def(">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toChar() >= b.toChar();
    });

    def("equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toChar() == b.toChar();
    });
}

CharacterClass::CharacterClass(Runtime *runtime)
    : RootClass(runtime, "Character", runtime->getObjectClass()) {
}
