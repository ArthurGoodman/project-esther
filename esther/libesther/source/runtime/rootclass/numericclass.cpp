#include "numericclass.h"

#include "esther.h"

NumericClass::NumericClass(Esther *esther)
    : RootClass(esther, "Numeric", esther->getObjectClass()) {
}

void NumericClass::setupMethods(Esther *esther) {
    defOper(esther, "+", [](const Variant &a, const Variant &b) -> Variant {
        return a + b;
    });

    defOper(esther, "-", [](const Variant &a, const Variant &b) -> Variant {
        return a - b;
    });

    defOper(esther, "*", [](const Variant &a, const Variant &b) -> Variant {
        return a * b;
    });

    defOper(esther, "/", [](const Variant &a, const Variant &b) -> Variant {
        return a / b;
    });

    defOper(esther, "%", [](const Variant &a, const Variant &b) -> Variant {
        return a % b;
    });

    defOper(esther, "**", [](const Variant &a, const Variant &b) -> Variant {
        return a.pow(b);
    });

    defPred(esther, "<", [](const Variant &a, const Variant &b) -> bool {
        return a < b;
    });

    defPred(esther, "<=", [](const Variant &a, const Variant &b) -> bool {
        return a <= b;
    });

    defPred(esther, ">", [](const Variant &a, const Variant &b) -> bool {
        return a > b;
    });

    defPred(esther, ">=", [](const Variant &a, const Variant &b) -> bool {
        return a >= b;
    });

    defPred(esther, "equals", [](const Variant &a, const Variant &b) -> bool {
        return a == b;
    });
}

void NumericClass::copy(ManagedObject *dst) {
    new (dst) NumericClass(*this);
}
