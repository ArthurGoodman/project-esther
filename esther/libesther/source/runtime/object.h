#pragma once

#include <map>
#include <string>
#include <vector>

class Class;
class Esther;

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

    Object *call(Esther *esther, const std::string &name, const std::vector<Object *> &args);
    Object *call(Esther *esther, Object *f, const std::vector<Object *> &args);
    Object *call(Esther *esther, const std::string &name, const std::vector<Object *> &args, Class *expectedReturnClass);

    Object *callIfFound(Esther *esther, const std::string &name, const std::vector<Object *> &args);
};
