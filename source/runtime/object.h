#pragma once
#include "common.h"

class Class;
class Tuple;

class Object {
    Class *objectClass;

    map<string, Object *> attributes;

public:
    Object();
    Object(Class *objectClass);
    Object(string className);

    virtual ~Object();

    Class *getClass();
    void setClass(Class *objectClass);

    virtual bool hasAttribute(string name);
    virtual Object *getAttribute(string name);
    virtual void setAttribute(string name, Object *value);

    bool is(Class *_class);
    bool is(string className);

    bool converts(Class *_class);

    Object *as(Class *_class);

    virtual Object *call(string name, Tuple *args);
    virtual Object *call(string name, Object *arg);
    virtual Object *call(string name);

    virtual bool isTrue();
    virtual bool isFalse();
    virtual bool isNull();

    virtual string toString();

    virtual bool equals(Object *other);
};
