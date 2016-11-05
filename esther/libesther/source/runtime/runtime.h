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

    void initialize();
    void release();

    Object *getMainObject();
    Class *getObjectClass();
    Object *getTrue();
    Object *getFalse();
    Object *getNull();

    Class *getRootClass(const std::string &name);

    Object *toBoolean(bool value);

private:
    void registerRootClass(Class *rootClass);
};
