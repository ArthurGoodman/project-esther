#pragma once

#include <map>
#include <string>
#include <vector>

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

    virtual Object *get(const std::string &name) const;

    bool is(Class *_class) const;

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Object *call(const std::string &name, const std::vector<Object *> &args);
    Object *callIfFound(const std::string &name, const std::vector<Object *> &args);
    Object *call(const std::string &name, const std::vector<Object *> &args, Class *expectedReturnClass);
};
