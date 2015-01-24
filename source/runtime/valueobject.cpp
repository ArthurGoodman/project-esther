#include "valueobject.h"

#include "esther.h"

namespace esther {

ValueObject::ValueObject(int value)
    : Object(Esther::getRootClass("Integer")), value(value) {
}

ValueObject::ValueObject(double value)
    : Object(Esther::getRootClass("Float")), value(value) {
}

ValueObject::ValueObject(char value)
    : Object(Esther::getRootClass("Char")), value(value) {
}

ValueObject::ValueObject(string value)
    : Object(Esther::getRootClass("String")), value(value) {
}

ValueObject::ValueObject(const char *value)
    : Object(Esther::getRootClass("String")), value(value) {
}

string ValueObject::toString() {
    return value.toString();
}
}
