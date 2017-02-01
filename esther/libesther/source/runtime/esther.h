#pragma once

#include <map>
#include <list>
#include <vector>
#include <functional>
#include <stack>

#include "variant/variant.h"
#include "common/source.h"

#include "memory/pointer.h"

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

class Esther {
    Pointer<Object> mainObject = nullptr;
    Pointer<RootClass> objectClass = nullptr;

    Pointer<Object> trueObject = nullptr;
    Pointer<Object> falseObject = nullptr;
    Pointer<Object> nullObject = nullptr;

    Pointer<NumericClass> numericClass = nullptr;
    Pointer<CharacterClass> characterClass = nullptr;
    Pointer<FloatClass> floatClass = nullptr;
    Pointer<IntegerClass> integerClass = nullptr;
    Pointer<StringClass> stringClass = nullptr;

    Pointer<ClassClass> classClass = nullptr;
    Pointer<FunctionClass> functionClass = nullptr;

    std::map<std::string, Pointer<RootClass>> rootClasses;

    std::stack<Source> sources;
    std::stack<std::string> fileNames;

    std::stack<Pointer<Context>> contexts;

    std::vector<Pointer<Object>> stack;
    Pointer<Object> reg;

public:
    static void runtimeError(const std::string &message);

    Esther();
    ~Esther();

    Pointer<Object> getMainObject() const;
    Pointer<Class> getObjectClass() const;
    Pointer<ClassClass> getClassClass() const;
    Pointer<Object> getTrue() const;
    Pointer<Object> getFalse() const;
    Pointer<Object> getNull() const;

    bool hasRootClass(const std::string &name) const;
    Pointer<Class> getRootClass(const std::string &name) const;
    void registerRootClass(Pointer<RootClass> rootClass);

    Pointer<Object> toBoolean(bool value) const;

    Pointer<Object> createObject();

    Pointer<Object> run(const std::string &script);
    Pointer<Object> runFile(const std::string &fileName);

    Pointer<Context> context() const;

    void pushContext(Pointer<Context> context);
    void popContext();

    void push(Pointer<Object> value);
    void pop(int count = 1);
    Pointer<Object> top(int index = 0);

    Pointer<Object> getReg() const;
    void setReg(Pointer<Object> value);

private:
    void initialize();
    void release();

    void setupMethods();

    void pushSource(const std::string &source);
    void popSource();

    void pushFileName(const std::string &fileName);
    void popFileName();

    const Source &source();
    const std::string &fileName();
};
