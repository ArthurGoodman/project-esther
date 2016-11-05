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
#include "true.h"
#include "false.h"
#include "null.h"

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

void Runtime::initialize() {
    rootClasses.clear();

    registerRootClass(classClass = new ClassClass());
    classClass->setClass(classClass);

    registerRootClass(objectClass = new ObjectClass(classClass));
    classClass->setSuperclass(objectClass);

    mainObject = objectClass->newInstance();

    BooleanClass *booleanClass;
    registerRootClass(booleanClass = new BooleanClass(classClass));

    trueObject = new True(booleanClass);
    falseObject = new False(booleanClass);

    NullClass *nullClass;
    registerRootClass(nullClass = new NullClass(classClass));

    nullObject = new Null(nullClass);

    registerRootClass(characterClass = new CharacterClass(classClass));
    registerRootClass(floatClass = new FloatClass(classClass));
    registerRootClass(integerClass = new IntegerClass(classClass));
    registerRootClass(stringClass = new StringClass(classClass));

    registerRootClass(functionClass = new FunctionClass(classClass));
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

Object *Runtime::createObject() {
    return objectClass->newInstance();
}

ValueObject *Runtime::createCharacter(char value) {
    return characterClass->createCharacter(value);
}

ValueObject *Runtime::createFloat(double value) {
    return floatClass->createFloat(value);
}

ValueObject *Runtime::createInteger(int value) {
    return integerClass->createInteger(value);
}

ValueObject *Runtime::createString(const std::string &value) {
    return stringClass->createString(value);
}

Class *Runtime::createClass(const std::string &name, Class *superclass) {
    return classClass->createClass(name, superclass);
}

Function *Runtime::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body) {
    return functionClass->createNativeFunction(name, arity, body);
}

Function *Runtime::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return functionClass->createInterpretedFunction(name, params, body, context);
}

void Runtime::registerRootClass(Class *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}
