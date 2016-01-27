#include "string.h"

String::String(string value)
    : ValueObject(value) {
}

String::String(const char *value)
    : ValueObject(string(value)) {
}

String::String()
    : ValueObject((string)"") {
}

void String::setValue(string value) {
    setVariant(Variant(value));
}

bool String::equals(Object *other) {
    return dynamic_cast<String *>(other) && value.toString() == ((String *)other)->value.toString();
}

string String::toString() {
    return value.toString();
}
