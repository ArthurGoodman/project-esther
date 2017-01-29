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

void StringClass::setupMethods(Esther *esther) {
    setAttribute("()", esther->createNativeFunction("()", 2, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
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

    defValueObjectFunc(esther, "initialize", -1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toString());

        return self;
    });

    defOper(esther, "+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString() + b.toString();
    });

    defPred(esther, "<", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() < b.toString();
    });

    defPred(esther, "<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() <= b.toString();
    });

    defPred(esther, ">", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() > b.toString();
    });

    defPred(esther, ">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() >= b.toString();
    });

    defPred(esther, "equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() == b.toString();
    });

    defFunc(esther, "size", [=](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->createInteger(((ValueObject *)self)->toString().size());
    });

    defOper(esther, "[]", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString()[b.toInteger()];
    });

    defPred(esther, "contains", [](const Variant &a, const Variant &b) -> bool {
        return a.toString().find(b.toChar()) != std::string::npos;
    });

    defValueObjectFunc(esther, "=", 1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toString());
        return self;
    });
}

StringClass::StringClass(Esther *esther)
    : RootClass(esther, "String", esther->getObjectClass()) {
}
