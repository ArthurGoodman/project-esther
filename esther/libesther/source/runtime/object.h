#pragma once

#include <map>
#include <string>

class Class;

class Object {
    Class *objectClass;
    std::map<std::string, Object *> attributes;

public:
    Object();
    Object(Class *objectClass);
    Object(const std::string &className);

    virtual ~Object();

    Class *getClass() const;

    bool hasAttribute(const std::string &name) const;
    Object *getAttribute(const std::string &name) const;
    void setAttribute(const std::string &name, Object *value);

    void clear();

    std::string toString() const;

    virtual bool isTrue() const;
};
