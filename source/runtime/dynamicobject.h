#pragma once

#include <map>
#include <string>

#include "iobject.h"

class Class;
class Tuple;

class DynamicObject : public IObject {
    Class *objectClass;

    std::map<std::string, IObject *> attributes;

public:
    DynamicObject();
    DynamicObject(Class *objectClass);
    DynamicObject(const std::string &className);

    Class *getClass();
    void setClass(Class *objectClass);

    virtual bool hasAttribute(const std::string &name);
    virtual IObject *getAttribute(const std::string &name);
    virtual void setAttribute(const std::string &name, IObject *value);

    bool is(Class *_class);
    bool is(const std::string &className);

    bool converts(Class *_class);

    IObject *as(Class *_class);

    virtual IObject *call(const std::string &name, Tuple *args);
    IObject *call(const std::string &name, IObject *arg, const std::string &expectedClassName);
    IObject *call(const std::string &name, const std::string &expectedClassName);

    virtual bool isTrue();
    virtual bool isFalse();

    bool callEquals(IObject *other);
    std::string callToString();

    virtual bool equals(IObject *other);
    virtual std::string toString();

    virtual IObject *clone();
};
