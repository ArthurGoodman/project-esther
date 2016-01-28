#pragma once
#include "common.h"

#include "iobject.h"

class Class;
class Tuple;

class DynamicObject : public IObject {
    Class *objectClass;

    map<string, IObject *> attributes;

public:
    DynamicObject();
    DynamicObject(Class *objectClass);
    DynamicObject(string className);

    Class *getClass();
    void setClass(Class *objectClass);

    virtual bool hasAttribute(string name);
    virtual IObject *getAttribute(string name);
    virtual void setAttribute(string name, IObject *value);

    bool is(Class *_class);
    bool is(string className);

    bool converts(Class *_class);

    IObject *as(Class *_class);

    virtual IObject *call(string name, Tuple *args);
    IObject *call(string name, IObject *arg, string expectedClassName);
    IObject *call(string name, string expectedClassName);

    virtual bool isTrue();
    virtual bool isFalse();

    bool callEquals(IObject *other);
    string callToString();

    virtual bool equals(IObject *other);
    virtual string toString();

    virtual IObject *clone();
};
