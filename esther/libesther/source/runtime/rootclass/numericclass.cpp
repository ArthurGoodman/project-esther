#include "numericclass.h"

#include "esther.h"

void NumericClass::setupMethods() {
    defOper("+", [](const Variant &a, const Variant &b) -> Variant {
        return a + b;
    });

    defOper("-", [](const Variant &a, const Variant &b) -> Variant {
        return a - b;
    });

    defOper("*", [](const Variant &a, const Variant &b) -> Variant {
        return a * b;
    });

    defOper("/", [](const Variant &a, const Variant &b) -> Variant {
        return a / b;
    });

    defOper("%", [](const Variant &a, const Variant &b) -> Variant {
        return a % b;
    });

    defOper("**", [](const Variant &a, const Variant &b) -> Variant {
        return a.pow(b);
    });

    defPred("<", [](const Variant &a, const Variant &b) -> bool {
        return a < b;
    });

    defPred("<=", [](const Variant &a, const Variant &b) -> bool {
        return a <= b;
    });

    defPred(">", [](const Variant &a, const Variant &b) -> bool {
        return a > b;
    });

    defPred(">=", [](const Variant &a, const Variant &b) -> bool {
        return a >= b;
    });

    defPred("equals", [](const Variant &a, const Variant &b) -> bool {
        return a == b;
    });
}

NumericClass::NumericClass(Esther *e)
    : RootClass(e, "Numeric", e->getObjectClass()) {
}
