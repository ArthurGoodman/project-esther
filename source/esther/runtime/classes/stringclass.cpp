#include "stringclass.h"

#include "runtime.h"
#include "string.h"

namespace esther {

StringClass::StringClass()
    : Class("String") {
    Runtime::setRootClass(this);
}

Object *StringClass::newInstance() {
    return new String();
}

void StringClass::setupMethods() {
}
}
