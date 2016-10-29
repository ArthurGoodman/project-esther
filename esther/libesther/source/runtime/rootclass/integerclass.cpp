#include "integerclass.h"

#include "valueobject.h"

Object *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

void IntegerClass::setupMethods() {
}

Object *IntegerClass::createNewInstance() {
    return createInteger(0);
}
