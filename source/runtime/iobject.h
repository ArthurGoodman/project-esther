#pragma once
#include "common.h"

class Class;
class Tuple;

class IObject {
public:
    virtual ~IObject();

    virtual Class *getClass() = 0;
    virtual void setClass(Class *objectClass) = 0;

    virtual bool hasAttribute(string name) = 0;
    virtual IObject *getAttribute(string name) = 0;
    virtual void setAttribute(string name, IObject *value) = 0;

    virtual bool is(Class *_class) = 0;
    virtual bool converts(Class *_class) = 0;
    virtual IObject *as(Class *_class) = 0;

    virtual IObject *call(string name, Tuple *args) = 0;
    IObject *call(string name, IObject *arg);
    IObject *call(string name);

    virtual bool isTrue() = 0;
    virtual bool isFalse() = 0;

    virtual bool callEquals(IObject *other) = 0;
    virtual string callToString() = 0;

    virtual bool equals(IObject *other) = 0;
    virtual string toString() = 0;

    virtual IObject *clone() = 0;
};
