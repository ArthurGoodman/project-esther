#pragma once

#include <map>

class Object;
class Class;
class Context;

class Runtime {
    static Context *root;

    static Object *mainObject;
    static Class *objectClass;

    static Object *trueObject;
    static Object *falseObject;
    static Object *nullObject;

    static std::map<std::string, Class *> rootClasses;

public:
    static void initialize();
    static void release();

    static Context *getRoot();
    static Object *getMainObject();
    static Class *getObjectClass();
    static Object *getTrue();
    static Object *getFalse();
    static Object *getNull();

    static bool hasRootClass(const std::string &name);
    static Class *getRootClass(const std::string &name);
    static void setRootClass(Class *rootClass);

    static Object *toBoolean(bool value);

    static void runtimeError(const std::string &message);
};
