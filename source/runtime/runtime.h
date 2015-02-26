#pragma once
#include "common.h"

class Object;
class Class;
class RootClass;
class Context;
class CallStack;
class Call;

// Global access point to the various runtime stuff.
class Runtime {
    static Context *root;

    static Object *mainObject;
    static Class *objectClass;

    static Object *trueObject;
    static Object *falseObject;
    static Object *nullObject;

    static map<string, RootClass *> rootClasses;

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
    static void setRootClass(RootClass *rootClass);

    static Object *toBoolean(bool value);

    static void runtimeError(string message);
};
