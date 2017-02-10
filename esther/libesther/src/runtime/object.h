#pragma once

#include <map>
#include <string>
#include <vector>

#include "memory/managedobject.h"

namespace es {

class Class;
class Esther;

class Object : public ManagedObject {
    Class *objectClass;
    std::map<std::string, Object *> *attributes;

public:
    Object(Class *volatile objectClass);

    virtual ~Object();

    Class *getClass() const;
    void setClass(Class *volatile objectClass);

    bool hasAttribute(const std::string &name) const;
    Object *getAttribute(const std::string &name) const;
    void setAttribute(const std::string &name, Object *volatile value);

    virtual Object *get(const std::string &name) const;

    bool is(Class *volatile _class) const;

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Object *call(Esther *esther, const std::string &name, const std::vector<Object *> &args);
    Object *call(Esther *esther, Object *volatile f, const std::vector<Object *> &args);
    Object *call(Esther *esther, const std::string &name, const std::vector<Object *> &args, Class *volatile expectedReturnClass);

    Object *callIfFound(Esther *esther, const std::string &name, const std::vector<Object *> &args);

    void finalize() override;
    void mapOnReferences(void (*f)(ManagedObject *&)) override;
};
}
