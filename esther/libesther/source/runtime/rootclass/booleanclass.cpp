#include "booleanclass.h"

#include "true.h"
#include "false.h"

Object *BooleanClass::createTrue() {
    return new True(this);
}

Object *BooleanClass::createFalse() {
    return new False(this);
}

void BooleanClass::setupMethods() {
}
