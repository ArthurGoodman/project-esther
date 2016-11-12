#include "stringclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance(const std::vector<Object *> &) {
    return createString("");
}

void StringClass::setupMethods() {
    def("+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString() + b.toString();
    });

    def("<", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() < b.toString();
    });

    def("<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() <= b.toString();
    });

    def(">", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() > b.toString();
    });

    def(">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() >= b.toString();
    });

    def("equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() == b.toString();
    });
}

StringClass::StringClass(Runtime *runtime)
    : RootClass(runtime, "String", runtime->getObjectClass()) {
}
