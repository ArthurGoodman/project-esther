#pragma once

#include <map>
#include <list>
#include <vector>
#include <functional>
#include <stack>

#include "variant/variant.h"
#include "common/source.h"

namespace es {

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
    Object *mainObject;
    RootClass *objectClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    NumericClass *numericClass;
    CharacterClass *characterClass;
    FloatClass *floatClass;
    IntegerClass *integerClass;
    StringClass *stringClass;

    ClassClass *classClass;
    FunctionClass *functionClass;

    std::map<std::string, RootClass *> rootClasses;

    std::stack<Source> sources;
    std::stack<std::string> fileNames;

    std::stack<Context *> contexts;

    std::vector<Object *> stack;
    Object *reg;

public:
    static void runtimeError(const char *fmt, ...);

    Esther();
    ~Esther();

    Object *getMainObject() const;
    Class *getObjectClass() const;
    ClassClass *getClassClass() const;
    Object *getTrue() const;
    Object *getFalse() const;
    Object *getNull() const;

    bool hasRootClass(const std::string &name) const;
    Class *getRootClass(const std::string &name) const;
    void registerRootClass(RootClass *rootClass);

    Object *toBoolean(bool value) const;

    Object *createObject();

    void run(const std::string &script);
    void runFile(const std::string &fileName);

    Context *context() const;

    void pushContext(Context *context);
    void popContext();

    void push(Object *value);
    void pop(int count = 1);
    Object *top(int index = 0);

    Object *getReg() const;
    void setReg(Object *value);

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
}
