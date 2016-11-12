#include "integerclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "numericclass.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance(const std::vector<Object *> &) {
    return createInteger(0);
}

void IntegerClass::setupMethods() {
}

IntegerClass::IntegerClass(Runtime *runtime)
    : RootClass(runtime, "Integer", runtime->getNumericClass()) {
}
