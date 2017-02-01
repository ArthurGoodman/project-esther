#include "numericclass.h"

#include "esther.h"

NumericClass::NumericClass(Esther *esther)
    : RootClass(esther, "Numeric", esther->getObjectClass()) {
}

void NumericClass::setupMethods(Esther *esther) {
    Pointer<NumericClass> _this = this;

    _this->defOper(esther, "+", [](const Variant &a, const Variant &b) -> Variant {
        return a + b;
    });

    _this->defOper(esther, "-", [](const Variant &a, const Variant &b) -> Variant {
        return a - b;
    });

    _this->defOper(esther, "*", [](const Variant &a, const Variant &b) -> Variant {
        return a * b;
    });

    _this->defOper(esther, "/", [](const Variant &a, const Variant &b) -> Variant {
        return a / b;
    });

    _this->defOper(esther, "%", [](const Variant &a, const Variant &b) -> Variant {
        return a % b;
    });

    _this->defOper(esther, "**", [](const Variant &a, const Variant &b) -> Variant {
        return a.pow(b);
    });

    _this->defPred(esther, "<", [](const Variant &a, const Variant &b) -> bool {
        return a < b;
    });

    _this->defPred(esther, "<=", [](const Variant &a, const Variant &b) -> bool {
        return a <= b;
    });

    _this->defPred(esther, ">", [](const Variant &a, const Variant &b) -> bool {
        return a > b;
    });

    _this->defPred(esther, ">=", [](const Variant &a, const Variant &b) -> bool {
        return a >= b;
    });

    _this->defPred(esther, "equals", [](const Variant &a, const Variant &b) -> bool {
        return a == b;
    });
}

void NumericClass::copy(ManagedObject *dst) {
    new (dst) NumericClass(*this);
}
