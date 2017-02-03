#include "runtime/rootclass/numericclass.h"

#include "esther.h"

namespace es {

NumericClass::NumericClass(Esther *esther)
    : RootClass(esther, "Numeric", esther->getObjectClass()) {
}

void NumericClass::setupMethods(Esther *esther) {
    Ptr<NumericClass> _this = this;

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
}
