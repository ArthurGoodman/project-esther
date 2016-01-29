#include "string.h"

String::String(const std::string &value)
    : ValueObject(value) {
}

String::String(const char *value)
    : ValueObject(std::string(value)) {
}

String::String()
    : ValueObject((std::string)"") {
}

void String::setValue(const std::string &value) {
    setVariant(Variant(value));
}

bool String::equals(IObject *other) {
    return dynamic_cast<String *>(other) && value.toString() == ((String *)other)->value.toString();
}

std::string String::toString() {
    return value.toString();
}
