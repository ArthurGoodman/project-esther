#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    std::string *name;
    Pointer<Class> superclass;

public:
    Class(Esther *esther, const std::string &name, Pointer<Class> superclass);
    ~Class();

    std::string getName() const;
    void setName(const std::string &name);

    Pointer<Class> getSuperclass() const;
    void setSuperclass(Pointer<Class> superclass);

    Pointer<Object> get(const std::string &name) const;

    Pointer<Object> newInstance(Esther *esther, const std::vector<Pointer<Object>> &args = std::vector<Pointer<Object>>());

    bool isChild(Pointer<Class> _class) const;

    std::string toString() const;

    Pointer<Object> lookup(const std::string &name) const;

    virtual void copy(ManagedObject *dst);
    virtual int getSize() const;

protected:
    virtual Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args);
};
