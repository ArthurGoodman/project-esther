#pragma once
#include <common.h>

namespace esther {

class Object;
class Class;
class Context;

class Lexer;
class Parser;

// Global access point to the various runtime stuff.
class Esther {
public:
    // External environment.
    static Context *root;

    static Object *mainObject;
    static Class *objectClass;

    static Object *trueObject;
    static Object *falseObject;
    static Object *nullObject;

    static map<string, Class *> rootClasses;

    // Internal environment.
    static Lexer *lexer;
    static Parser *parser;
    static stack<string> sources; // This is used in error messages to show the line containing errors.

public:
    static void initialize();
    static void release();

    static void initializeRuntime();

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
//    static void setRootClass(string name, string superName);

    static Object *toBoolean(bool value);

    static void pushSource(const string &source);
    static void popSource();

    // Current source code access point.
    static const string &source();
};
}
