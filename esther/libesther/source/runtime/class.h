#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    friend class ClassClass;

    std::string name;
    Pointer<Class> superclass;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Pointer<Class> getSuperclass() const;
    void setSuperclass(Pointer<Class> superclass);

    Pointer<Object> get(const std::string &name) const;

    Pointer<Object> newInstance(Esther *esther, const std::vector<Pointer<Object>> &args = std::vector<Pointer<Object>>());

    bool isChild(Pointer<Class> _class) const;

    std::string toString() const;

    Pointer<Object> lookup(const std::string &name) const;

protected:
    Class(Pointer<Class> classClass, const std::string &name, Pointer<Class> superclass);

    virtual Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);
};
