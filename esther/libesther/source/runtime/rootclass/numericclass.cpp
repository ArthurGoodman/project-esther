#include "numericclass.h"

#include "runtime.h"

void NumericClass::setupMethods() {
    def("+", [](const Variant &a, const Variant &b) -> Variant {
        return a + b;
    });

    def("-", [](const Variant &a, const Variant &b) -> Variant {
        return a - b;
    });

    def("*", [](const Variant &a, const Variant &b) -> Variant {
        return a * b;
    });

    def("/", [](const Variant &a, const Variant &b) -> Variant {
        return a / b;
    });

    def("%", [](const Variant &a, const Variant &b) -> Variant {
        return a % b;
    });

    def("<", [](const Variant &a, const Variant &b) -> bool {
        return a < b;
    });

    def("<=", [](const Variant &a, const Variant &b) -> bool {
        return a <= b;
    });

    def(">", [](const Variant &a, const Variant &b) -> bool {
        return a > b;
    });

    def(">=", [](const Variant &a, const Variant &b) -> bool {
        return a >= b;
    });

    def("equals", [](const Variant &a, const Variant &b) -> bool {
        return a == b;
    });
}

NumericClass::NumericClass(Runtime *runtime)
    : RootClass(runtime, "Numeric", runtime->getObjectClass()) {
}
