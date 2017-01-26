#include "stringclass.h"

#include "valueobject.h"
#include "esther.h"
#include "function.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance(const std::vector<Object *> &) {
    return createString("");
}

void StringClass::setupMethods() {
    setAttribute("()", esther->createNativeFunction("()", 2, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<StringClass *>(self)) {
            Esther::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Esther::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return esther->createString(((ValueObject *)args[1])->getVariant().toString());
    }));

    defValueObjectFunc("initialize", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toString());

        return self;
    });

    defOper("+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString() + b.toString();
    });

    defPred("<", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() < b.toString();
    });

    defPred("<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() <= b.toString();
    });

    defPred(">", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() > b.toString();
    });

    defPred(">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() >= b.toString();
    });

    defPred("equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() == b.toString();
    });

    defFunc("size", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return esther->createInteger(((ValueObject *)self)->toString().size());
    });

    defOper("[]", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString()[b.toInteger()];
    });

    defPred("contains", [](const Variant &a, const Variant &b) -> bool {
        return a.toString().find(b.toChar()) != std::string::npos;
    });

    defValueObjectFunc("=", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toString());
        return self;
    });
}

StringClass::StringClass(Esther *e)
    : RootClass(e, "String", e->getObjectClass()) {
}
