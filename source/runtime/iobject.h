#pragma once

#include <string>

class Class;
class Tuple;

class IObject {
public:
    virtual ~IObject();

    virtual Class *getClass() = 0;
    virtual void setClass(Class *objectClass) = 0;

    virtual bool hasAttribute(const std::string &name) = 0;
    virtual IObject *getAttribute(const std::string &name) = 0;
    virtual void setAttribute(const std::string &name, IObject *value) = 0;

    virtual bool is(Class *_class) = 0;
    virtual bool converts(Class *_class) = 0;
    virtual IObject *as(Class *_class) = 0;

    virtual IObject *call(const std::string &name, Tuple *args) = 0;
    IObject *call(const std::string &name, IObject *arg);
    IObject *call(const std::string &name);

    virtual bool isTrue() = 0;
    virtual bool isFalse() = 0;

    virtual bool callEquals(IObject *other) = 0;
    virtual std::string callToString() = 0;

    virtual bool equals(IObject *other) = 0;
    virtual std::string toString() = 0;

    virtual IObject *clone() = 0;
};
