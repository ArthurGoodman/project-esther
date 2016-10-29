#include "stringclass.h"

#include "valueobject.h"

Object *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

void StringClass::setupMethods() {
}

Object *StringClass::createNewInstance() {
    return createString("");
}
