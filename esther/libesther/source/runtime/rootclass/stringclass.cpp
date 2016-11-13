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

    def("initialize", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Runtime::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty()) {
            if (!dynamic_cast<ValueObject *>(args[0])) {
                Runtime::runtimeError(getName() + ".initialize: invalid argument");
                return nullptr;
            }

            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toString());
        }

        return self;
    });

    def("+=", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<ValueObject *>(args[0])) {
            Runtime::runtimeError(getName() + ".+=: invalid argument");
            return nullptr;
        }

        ((ValueObject *)self)->setVariant(((ValueObject *)self)->getVariant() + ((ValueObject *)args[0])->getVariant().toString());

        return self;
    });

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

    def("size", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return runtime->createInteger(((ValueObject *)self)->toString().size());
    });

    def("[]", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString()[b.toInteger()];
    });

    def("contains", [](const Variant &a, const Variant &b) -> bool {
        return a.toString().find(b.toChar()) != std::string::npos;
    });
}

StringClass::StringClass(Runtime *runtime)
    : RootClass(runtime, "String", runtime->getObjectClass()) {
}
