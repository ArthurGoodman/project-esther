#include "runtime/rootclass/stringclass.h"

#include "runtime/valueobject.h"
#include "esther.h"
#include "runtime/nativefunction.h"

namespace es {

StringClass::StringClass(Esther *esther)
    : RootClass(esther, "String", esther->getObjectClass()) {
}

void StringClass::setupMethods(Esther *esther) {
    setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther * esther, Object * volatile self, const std::vector<Object *> &args) -> Object * {
                     if (!dynamic_cast<StringClass *volatile>(self)) {
                         Esther::runtimeError("String.(): invalid self");
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *volatile>(args[1])) {
                         Esther::runtimeError("String.(): invalid argument");
                         return nullptr;
                     }

                     return new ValueObject(esther, static_cast<ValueObject *volatile>(args[1])->getVariant().toString());
                 }));

    defValueObjectFunc(esther, "initialize", -1, [](Esther *, Object * volatile self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError("String.initialize: invalid number of arguments");

        if (!args.empty())
            static_cast<ValueObject *volatile>(self)->setVariant(static_cast<ValueObject *volatile>(args[0])->getVariant().toString());

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

    defFunc(esther, "size", [](Esther * esther, Object * volatile self, const std::vector<Object *> &) -> Object * {
        return new ValueObject(esther, static_cast<int>(static_cast<ValueObject *volatile>(self)->toString().size()));
    });

    defOper(esther, "[]", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString()[b.toInteger()];
    });

    defPred(esther, "contains", [](const Variant &a, const Variant &b) -> bool {
        return a.toString().find(b.toChar()) != std::string::npos;
    });

    defValueObjectFunc(esther, "=", 1, [](Esther *, Object * volatile self, const std::vector<Object *> &args) -> Object * {
        static_cast<ValueObject *volatile>(self)->setVariant(static_cast<ValueObject *volatile>(args[0])->getVariant().toString());
        return self;
    });
}

Object *StringClass::createNewInstance(Esther *esther, const std::vector<Object *> &) {
    return new ValueObject(esther, "");
}
}
