#pragma once
#include <common.h>

namespace esther {

class Class;

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
    bool converts(Class *_class);

    Object *as(Class *_class);

    Object *call(string name, list<Object *> args);
    Object *call(string name, Object *arg);
    Object *call(string name);

    virtual bool isTrue();
    virtual bool isFalse();
    virtual bool isNull();

    virtual string toString();
};
}
