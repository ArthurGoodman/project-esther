#include "stringclass.h"

#include "valueobject.h"
#include "esther.h"
#include "nativefunction.h"

StringClass::StringClass(Esther *esther)
    : RootClass(esther, "String", esther->getObjectClass()) {
}

void StringClass::setupMethods(Esther *esther) {
    Pointer<StringClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                            if (!dynamic_cast<StringClass *>(*self)) {
                                Esther::runtimeError("String.(): invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[1])) {
                                Esther::runtimeError("String.(): invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, ((ValueObject *)*args[1])->getVariant().toString());
                        }));

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("String.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toString());

        return self;
    });

    _this->defOper(esther, "+", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString() + b.toString();
    });

    _this->defPred(esther, "<", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() < b.toString();
    });

    _this->defPred(esther, "<=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() <= b.toString();
    });

    _this->defPred(esther, ">", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() > b.toString();
    });

    _this->defPred(esther, ">=", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() >= b.toString();
    });

    _this->defPred(esther, "equals", [](const Variant &a, const Variant &b) -> bool {
        return a.toString() == b.toString();
    });

    _this->defFunc(esther, "size", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return new ValueObject(esther, (int)((ValueObject *)*self)->toString().size());
    });

    _this->defOper(esther, "[]", [](const Variant &a, const Variant &b) -> Variant {
        return a.toString()[b.toInteger()];
    });

    _this->defPred(esther, "contains", [](const Variant &a, const Variant &b) -> bool {
        return a.toString().find(b.toChar()) != std::string::npos;
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toString());
        return self;
    });
}

void StringClass::copy(ManagedObject *dst) {
    new (dst) StringClass(*this);
}

Pointer<Object> StringClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new ValueObject(esther, "");
}
