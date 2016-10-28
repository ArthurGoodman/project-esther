#include "nullclass.h"

#include "null.h"

Object *NullClass::createNull() {
     return new Null(this);
}

void NullClass::setupMethods() {
}
