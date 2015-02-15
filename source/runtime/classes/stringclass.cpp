#include "stringclass.h"

#include "runtime.h"
#include "string.h"

StringClass::StringClass()
    : RootClass("String") {
}

Object *StringClass::newInstance() {
    return new String();
}

void StringClass::setupMethods() {
}
