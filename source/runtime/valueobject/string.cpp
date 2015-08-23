#include "string.h"

String::String(string value)
    : ValueObject(value) {
}

String::String(const char *value)
    : ValueObject(string(value)) {
}

String::String()
    : ValueObject("") {
}

void String::setValue(string value) {
    setVariant(Variant(value));
}
