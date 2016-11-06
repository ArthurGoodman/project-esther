#include "integerclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance() {
    return createInteger(0);
}

void IntegerClass::setupMethods() {
    def("+", [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->createInteger(((ValueObject *)self)->getVariant().toInteger() + ((ValueObject *)args[0])->getVariant().toInteger());
    });

    def("<", [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(((ValueObject *)self)->getVariant().toInteger() < ((ValueObject *)args[0])->getVariant().toInteger());
    });
}

IntegerClass::IntegerClass(Runtime *runtime, Class *objectClass)
    : RootClass(runtime, objectClass, "Integer", objectClass->getSuperclass()) {
}
