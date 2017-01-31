#pragma once

#include <map>
#include <string>
#include <vector>

#include "memory/managedobject.h"
#include "memory/pointer.h"

class Class;
class Esther;

class Object : public ManagedObject {
    Pointer<Class> objectClass;
    std::map<std::string, Pointer<Object>> attributes;

public:
    Object(Pointer<Class> objectClass);

    virtual ~Object();

    Pointer<Class> getClass() const;
    void setClass(Pointer<Class> objectClass);

    bool hasAttribute(const std::string &name) const;
    Pointer<Object> getAttribute(const std::string &name) const;
    void setAttribute(const std::string &name, Pointer<Object> value);

    virtual Pointer<Object> get(const std::string &name) const;

    bool is(Pointer<Class> _class) const;

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Pointer<Object> call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args);
    Pointer<Object> call(Esther *esther, Pointer<Object> f, const std::vector<Pointer<Object>> &args);
    Pointer<Object> call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args, Pointer<Class> expectedReturnClass);

    Pointer<Object> callIfFound(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args);

    virtual void copy(ManagedObject *dst);
    virtual int getSize() const;
};
