#include "integerclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "numericclass.h"
#include "function.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance(const std::vector<Object *> &) {
    return createInteger(0);
}

void IntegerClass::setupMethods() {
    setAttribute("()", runtime->createNativeFunction("()", 2, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<IntegerClass *>(self)) {
            Runtime::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Runtime::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return runtime->createInteger(((ValueObject *)args[1])->getVariant().toInteger());
    }));
}

IntegerClass::IntegerClass(Runtime *runtime)
    : RootClass(runtime, "Integer", runtime->getNumericClass()) {
}
