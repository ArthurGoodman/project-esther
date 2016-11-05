#pragma once

#include <map>
#include <list>
#include <vector>
#include <functional>

#include "variant/variant.h"

class Object;
class Class;
class Context;
class ValueObject;
class Function;
class Expression;

class CharacterClass;
class FloatClass;
class IntegerClass;
class StringClass;

class ClassClass;
class FunctionClass;

class Runtime {
    Object *mainObject;
    Class *objectClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    std::map<std::string, Class *> rootClasses;

    CharacterClass *characterClass;
    FloatClass *floatClass;
    IntegerClass *integerClass;
    StringClass *stringClass;

    ClassClass *classClass;
    FunctionClass *functionClass;

public:
    static void runtimeError(const std::string &message);

    void initialize();
    void release();

    Object *getMainObject();
    Class *getObjectClass();
    Object *getTrue();
    Object *getFalse();
    Object *getNull();

    Class *getRootClass(const std::string &name);

    Object *toBoolean(bool value);

    Object *createObject();

    ValueObject *createValueObject(const Variant &value);

    ValueObject *createCharacter(char value);
    ValueObject *createFloat(double value);
    ValueObject *createInteger(int value);
    ValueObject *createString(const std::string &value);

    Class *createClass(const std::string &name, Class *superclass = nullptr);

    Function *createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
    Function *createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);

private:
    void registerRootClass(Class *rootClass);
};
