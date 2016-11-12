#include "floatclass.h"

#include <cmath>

#include "valueobject.h"
#include "runtime.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance(const std::vector<Object *> &) {
    return createFloat(0.0);
}

void FloatClass::setupMethods() {
    def("+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toReal() + b.toReal();
    });

    def("-", [](const Variant &a, const Variant &b) -> Variant {
        return a.toReal() - b.toReal();
    });

    def("*", [](const Variant &a, const Variant &b) -> Variant {
        return a.toReal() * b.toReal();
    });

    def("/", [](const Variant &a, const Variant &b) -> Variant {
        return a.toReal() / b.toReal();
    });

    def("%", [](const Variant &a, const Variant &b) -> Variant {
        return fmod(a.toReal(), b.toReal());
    });

    def("<", [](const Variant &a, const Variant &b) -> bool {
        return a.toReal() < b.toReal();
    });

    def("<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toReal() <= b.toReal();
    });

    def(">", [](const Variant &a, const Variant &b) -> bool {
        return a.toReal() > b.toReal();
    });

    def(">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toReal() >= b.toReal();
    });

    def("equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toReal() == b.toReal();
    });
}

FloatClass::FloatClass(Runtime *runtime)
    : RootClass(runtime, "Float", runtime->getObjectClass()) {
}
