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
    Ptr<Object> mainObject = nullptr;
    Ptr<RootClass> objectClass = nullptr;

    Ptr<Object> trueObject = nullptr;
    Ptr<Object> falseObject = nullptr;
    Ptr<Object> nullObject = nullptr;

    Ptr<NumericClass> numericClass = nullptr;
    Ptr<CharacterClass> characterClass = nullptr;
    Ptr<FloatClass> floatClass = nullptr;
    Ptr<IntegerClass> integerClass = nullptr;
    Ptr<StringClass> stringClass = nullptr;

    Ptr<ClassClass> classClass = nullptr;
    Ptr<FunctionClass> functionClass = nullptr;

    std::map<std::string, Ptr<RootClass>> rootClasses;

    std::stack<Source> sources;
    std::stack<std::string> fileNames;

    std::stack<Ptr<Context>> contexts;

    std::vector<Ptr<Object>> stack;
    Ptr<Object> reg;

public:
    static void runtimeError(const std::string &message);

    Esther();
    ~Esther();

    Ptr<Object> getMainObject() const;
    Ptr<Class> getObjectClass() const;
    Ptr<ClassClass> getClassClass() const;
    Ptr<Object> getTrue() const;
    Ptr<Object> getFalse() const;
    Ptr<Object> getNull() const;

    bool hasRootClass(const std::string &name) const;
    Ptr<Class> getRootClass(const std::string &name) const;
    void registerRootClass(Ptr<RootClass> rootClass);

    Ptr<Object> toBoolean(bool value) const;

    Ptr<Object> createObject();

    Ptr<Object> run(const std::string &script);
    Ptr<Object> runFile(const std::string &fileName);

    Ptr<Context> context() const;

    void pushContext(Ptr<Context> context);
    void popContext();

    void push(Ptr<Object> value);
    void pop(int count = 1);
    Ptr<Object> top(int index = 0);

    Ptr<Object> getReg() const;
    void setReg(Ptr<Object> value);

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
