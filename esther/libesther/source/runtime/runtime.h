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

class RootClass;

class NumericClass;
class CharacterClass;
class FloatClass;
class IntegerClass;
class StringClass;

class ClassClass;
class FunctionClass;

class Runtime {
    Object *mainObject = nullptr;
    RootClass *objectClass = nullptr;

    Object *trueObject = nullptr;
    Object *falseObject = nullptr;
    Object *nullObject = nullptr;

    NumericClass *numericClass = nullptr;
    CharacterClass *characterClass = nullptr;
    FloatClass *floatClass = nullptr;
    IntegerClass *integerClass = nullptr;
    StringClass *stringClass = nullptr;

    ClassClass *classClass = nullptr;
    FunctionClass *functionClass = nullptr;

    std::map<std::string, RootClass *> rootClasses;

public:
    static void runtimeError(const std::string &message);

    void initialize();
    void release();

    Object *getMainObject() const;
    Class *getObjectClass() const;
    Object *getTrue() const;
    Object *getFalse() const;
    Object *getNull() const;

    ClassClass *getClassClass() const;
    NumericClass *getNumericClass() const;
    StringClass *getStringClass() const;

    bool hasRootClass(const std::string &name) const;
    Class *getRootClass(const std::string &name) const;
    void registerRootClass(RootClass *rootClass);

    Object *toBoolean(bool value) const;

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
    void setupMethods();
};

Object *runtimeCreateNewObject(Context *context...);
