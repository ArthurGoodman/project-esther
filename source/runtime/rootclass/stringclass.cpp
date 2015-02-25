#include "stringclass.h"

#include "runtime.h"
#include "string.h"
#include "tuple.h"

StringClass::StringClass()
    : RootClass("String") {
}

Object *StringClass::newInstance() {
    return new String();
}

Object *StringClass::newInstance(Tuple *args) {
    return new String(args->at(0)->toString());
}

void StringClass::setupMethods() {
}
