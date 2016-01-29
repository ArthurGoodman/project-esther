#pragma once

#include <map>

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

    static std::map<std::string, RootClass *> rootClasses;

public:
    static void initialize();
    static void release();

    static Context *getRoot();
    static IObject *getMainObject();
    static Class *getObjectClass();
    static IObject *getTrue();
    static IObject *getFalse();
    static IObject *getNull();

    static bool hasRootClass(const std::string &name);
    static Class *getRootClass(const std::string &name);
    static void setRootClass(RootClass *rootClass);

    static IObject *toBoolean(bool value);

    static void runtimeError(const std::string &message);
};
