#pragma once
#include "common.h"

class IObject;
class Class;
class RootClass;
class Context;
class CallStack;
class Call;

class Runtime {
    static Context *root;

    static IObject *mainObject;
    static Class *objectClass;

    static IObject *trueObject;
    static IObject *falseObject;
    static IObject *nullObject;

    static map<string, RootClass *> rootClasses;

public:
    static void initialize();
    static void release();

    static Context *getRoot();
    static IObject *getMainObject();
    static Class *getObjectClass();
    static IObject *getTrue();
    static IObject *getFalse();
    static IObject *getNull();

    static bool hasRootClass(string name);
    static Class *getRootClass(string name);
    static void setRootClass(RootClass *rootClass);

    static IObject *toBoolean(bool value);

    static void runtimeError(string message);
};
