#include "runtime.h"

#include "class.h"
#include "runtimeerror.h"
#include "booleanclass.h"
#include "characterclass.h"
#include "floatclass.h"
#include "classclass.h"
#include "functionclass.h"
#include "integerclass.h"
#include "nullclass.h"
#include "objectclass.h"
#include "stringclass.h"

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

void Runtime::initialize() {
    rootClasses.clear();

    ClassClass *classClass = new ClassClass();
    registerRootClass(classClass);
    classClass->setClass(classClass);

    objectClass = classClass->createObjectClass();
    registerRootClass(objectClass);

    classClass->setSuperclass(objectClass);

    mainObject = objectClass->newInstance();

    BooleanClass *booleanClass = classClass->createBooleanClass();
    registerRootClass(booleanClass);

    trueObject = booleanClass->createTrue();
    falseObject = booleanClass->createFalse();

    NullClass *nullClass = classClass->createNullClass();
    registerRootClass(nullClass);

    nullObject = nullClass->createNull();

    registerRootClass(classClass->createCharacterClass());
    registerRootClass(classClass->createFloatClass());
    registerRootClass(classClass->createIntegerClass());
    registerRootClass(classClass->createStringClass());

    registerRootClass(classClass->createFunctionClass());
}

void Runtime::release() {
}

Object *Runtime::getMainObject() {
    return mainObject;
}

Class *Runtime::getObjectClass() {
    return objectClass;
}

Object *Runtime::getTrue() {
    return trueObject;
}

Object *Runtime::getFalse() {
    return falseObject;
}

Object *Runtime::getNull() {
    return nullObject;
}

Class *Runtime::getRootClass(const std::string &name) {
    return rootClasses[name];
}

Object *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Runtime::registerRootClass(Class *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}
