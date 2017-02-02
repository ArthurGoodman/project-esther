#pragma once

#include <map>
#include <string>
#include <vector>

#include "memory/managedobject.h"
#include "memory/pointer.h"

class Class;
class Esther;

class Object : public ManagedObject {
    Class *objectClass;
    std::map<std::string, Object *> *attributes;

public:
    Object(Ptr<Class> objectClass);

    virtual ~Object();

    Ptr<Class> getClass() const;
    void setClass(Ptr<Class> objectClass);

    bool hasAttribute(const std::string &name) const;
    Ptr<Object> getAttribute(const std::string &name) const;
    void setAttribute(const std::string &name, Ptr<Object> value);

    virtual Ptr<Object> get(const std::string &name) const;

    bool is(Ptr<Class> _class) const;

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Ptr<Object> call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args);
    Ptr<Object> call(Esther *esther, Ptr<Object> f, const std::vector<Ptr<Object>> &args);
    Ptr<Object> call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args, Ptr<Class> expectedReturnClass);

    Ptr<Object> callIfFound(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args);

    void mapOnReferences(const std::function<void (ManagedObject *&)> &f) override;
    int getSize() const override;
};
