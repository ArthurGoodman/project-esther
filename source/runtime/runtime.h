#pragma once
#include "common.h"

namespace esther {

class Object;
class Class;
class Context;

// Global access point to the various runtime stuff.
class Runtime {
    static Context *root;

    static Object *mainObject;
    static Class *objectClass;

    static Object *trueObject;
    static Object *falseObject;
    static Object *nullObject;

    static map<string, Class *> rootClasses;

public:
    static void initialize();
    static void release();

    static Context *getRoot();
    static Object *getMainObject();
    static Class *getObjectClass();
    static Object *getTrue();
    static Object *getFalse();
    static Object *getNull();

    static bool hasRootClass(string name);
    static Class *getRootClass(string name);
    static void setRootClass(Class *rootClass);
    static void setRootClass(string name);
    static void setRootClass(string name, string superName);

    static Object *toBoolean(bool value);

    static void runtimeError(string message);
};
}
