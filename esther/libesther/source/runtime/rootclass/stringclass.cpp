#include "stringclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance() {
    return createString("");
}

void StringClass::setupMethods() {
}

StringClass::StringClass(Runtime *runtime)
    : RootClass(runtime, "String", runtime->getObjectClass()) {
}
