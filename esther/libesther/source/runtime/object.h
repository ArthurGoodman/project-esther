#pragma once

#include <map>
#include <string>
#include <list>

class Class;

class Object {
    Class *objectClass;
    std::map<std::string, Object *> attributes;

public:
    Object(Class *objectClass);

    virtual ~Object();

    Class *getClass() const;
    void setClass(Class *objectClass);

    bool hasAttribute(const std::string &name) const;
    Object *getAttribute(const std::string &name) const;
    void setAttribute(const std::string &name, Object *value);

    void clear();

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Object *call(const std::string &name, const std::list<Object *> &args);
};
