#include "stringclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "function.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance(const std::vector<Object *> &) {
    return createString("");
}

void StringClass::setupMethods() {
    setAttribute("()", runtime->createNativeFunction("()", 2, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<StringClass *>(self)) {
            Runtime::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Runtime::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return runtime->createString(((ValueObject *)args[1])->getVariant().toString());
    }));

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
