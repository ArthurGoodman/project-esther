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
#include "context.h"

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

void Runtime::initialize() {
    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(objectClass);

    mainObject = createObject();

    BooleanClass *booleanClass = new BooleanClass(this);

    trueObject = new True(booleanClass);
    falseObject = new False(booleanClass);

    NullClass *nullClass = new NullClass(this);

    nullObject = new Null(nullClass);

    characterClass = new CharacterClass(this);
    floatClass = new FloatClass(this);
    integerClass = new IntegerClass(this);
    stringClass = new StringClass(this);

    functionClass = new FunctionClass(this);

    setupMethods();
}

void Runtime::release() {
}

Object *Runtime::getMainObject() const {
    return mainObject;
}

Class *Runtime::getObjectClass() const {
    return objectClass;
}

Object *Runtime::getTrue() const {
    return trueObject;
}

Object *Runtime::getFalse() const {
    return falseObject;
}

Object *Runtime::getNull() const {
    return nullObject;
}

ClassClass *Runtime::getClassClass() const {
    return classClass;
}

bool Runtime::hasRootClass(const std::string &name) const {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Runtime::getRootClass(const std::string &name) const {
    return rootClasses.at(name);
}

void Runtime::registerRootClass(RootClass *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Object *Runtime::toBoolean(bool value) const {
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

void Runtime::setupMethods() {
    for (auto &rootClass : rootClasses)
        rootClass.second->setupMethods();
}

Object *runtimeCreateNewObject(Context *context...) {
    return context->getRuntime()->createObject();
}
