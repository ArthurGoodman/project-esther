#pragma once

#include <string>

#include "runtime/object.h"

namespace es {

class Class : public Object {
    std::string name;
    Class *superclass;

public:
    Class(Esther *esther, const std::string &name, Class *superclass);

    std::string getName() const;
    void setName(const std::string &name);

    Class *getSuperclass() const;
    void setSuperclass(Class *superclass);

    Object *get(const std::string &name) const override;

    Object *newInstance(Esther *esther, const std::vector<Object *> &args = std::vector<Object *>());

    bool isChild(Class *_class) const;

    std::string toString() const override;

    Object *lookup(const std::string &name) const;

protected:
    virtual Object *createNewInstance(Esther *esther, const std::vector<Object *> &args);
};
}
