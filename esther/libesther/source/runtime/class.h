#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    std::string *name;
    Class *superclass;

public:
    Class(Esther *esther, const std::string &name, Ptr<Class> superclass);
    ~Class();

    std::string getName() const;
    void setName(const std::string &name);

    Ptr<Class> getSuperclass() const;
    void setSuperclass(Ptr<Class> superclass);

    Ptr<Object> get(const std::string &name) const override;

    Ptr<Object> newInstance(Esther *esther, const std::vector<Ptr<Object>> &args = std::vector<Ptr<Object>>());

    bool isChild(Ptr<Class> _class) const;

    std::string toString() const override;

    Ptr<Object> lookup(const std::string &name) const;

    void mapOnReferences(const std::function<void(ManagedObject *&)> &f) override;
    int getSize() const override;

protected:
    virtual Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args);
};
