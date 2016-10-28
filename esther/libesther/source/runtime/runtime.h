#pragma once

#include <map>

class Object;
class Class;
class Context;

class Runtime {
    Object *mainObject;
    Class *objectClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    std::map<std::string, Class *> rootClasses;

public:
    static void runtimeError(const std::string &message);

    Runtime();
    ~Runtime();

    Object *getMainObject();
    Class *getObjectClass();
    Object *getTrue();
    Object *getFalse();
    Object *getNull();

    bool hasRootClass(const std::string &name);
    Class *getRootClass(const std::string &name);
    void setRootClass(Class *rootClass);

    Object *toBoolean(bool value);

private:
    void initialize();
    void release();
};
