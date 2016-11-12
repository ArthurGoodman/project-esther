#include "integerclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance(const std::vector<Object *> &) {
    return createInteger(0);
}

void IntegerClass::setupMethods() {
    def("+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toInteger() + b.toInteger();
    });

    def("-", [](const Variant &a, const Variant &b) -> Variant {
        return a.toInteger() - b.toInteger();
    });

    def("*", [](const Variant &a, const Variant &b) -> Variant {
        return a.toInteger() * b.toInteger();
    });

    def("/", [](const Variant &a, const Variant &b) -> Variant {
        return a.toInteger() / b.toInteger();
    });

    def("%", [](const Variant &a, const Variant &b) -> Variant {
        return a.toInteger() % b.toInteger();
    });

    def("<", [](const Variant &a, const Variant &b) -> bool {
        return a.toInteger() < b.toInteger();
    });

    def("<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toInteger() <= b.toInteger();
    });

    def(">", [](const Variant &a, const Variant &b) -> bool {
        return a.toInteger() > b.toInteger();
    });

    def(">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toInteger() >= b.toInteger();
    });

    def("equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toInteger() == b.toInteger();
    });
}

IntegerClass::IntegerClass(Runtime *runtime)
    : RootClass(runtime, "Integer", runtime->getObjectClass()) {
}
