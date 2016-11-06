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
#include "function.h"
#include "valueobject.h"

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

void Runtime::initialize() {
    rootClasses.clear();

    registerRootClass(classClass = new ClassClass(this));
    classClass->setClass(classClass);

    registerRootClass(objectClass = new ObjectClass(this, classClass));
    classClass->setSuperclass(objectClass);

    mainObject = objectClass->newInstance();

    BooleanClass *booleanClass;
    registerRootClass(booleanClass = new BooleanClass(this, classClass));

    trueObject = new True(booleanClass);
    falseObject = new False(booleanClass);

    NullClass *nullClass;
    registerRootClass(nullClass = new NullClass(this, classClass));

    nullObject = new Null(nullClass);

    registerRootClass(characterClass = new CharacterClass(this, classClass));
    registerRootClass(floatClass = new FloatClass(this, classClass));
    registerRootClass(integerClass = new IntegerClass(this, classClass));
    registerRootClass(stringClass = new StringClass(this, classClass));

    registerRootClass(functionClass = new FunctionClass(this, classClass));

    setupMethods();
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

CharacterClass *Runtime::getCharacterClass() {
    return characterClass;
}

FloatClass *Runtime::getFloatClass() {
    return floatClass;
}

IntegerClass *Runtime::getIntegerClass() {
    return integerClass;
}

StringClass *Runtime::getStringClass() {
    return stringClass;
}

ClassClass *Runtime::getClassClass() {
    return classClass;
}

FunctionClass *Runtime::getFunctionClass() {
    return functionClass;
}

Object *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

Object *Runtime::createObject() {
    return objectClass->newInstance();
}

ValueObject *Runtime::createValueObject(const Variant &value) {
    switch (value.getType()) {
    case Variant::Integer:
        return createInteger(value.toInteger());

    case Variant::Real:
        return createFloat(value.toReal());

    case Variant::Char:
        return createCharacter(value.toChar());

    case Variant::String:
        return createString(value.toString());

    default:
        return nullptr;
    }
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

Function *Runtime::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    return functionClass->createNativeFunction(name, arity, body);
}

Function *Runtime::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return functionClass->createInterpretedFunction(name, params, body, context);
}

void Runtime::registerRootClass(RootClass *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

void Runtime::setupMethods() {
    for (auto &rootClass : rootClasses)
        rootClass.second->setupMethods();
}
