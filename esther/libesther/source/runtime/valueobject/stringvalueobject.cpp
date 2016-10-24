#include "stringvalueobject.h"

String::String(const std::string &value)
    : ValueObject(value) {
}

String::String(const char *value)
    : ValueObject((std::string)(value)) {
}

String::String()
    : ValueObject((std::string) "") {
}

void String::setValue(const std::string &value) {
    setVariant(Variant(value));
}

std::string String::toString() {
    return value.toString();
}
