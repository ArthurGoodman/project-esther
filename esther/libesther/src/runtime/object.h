#pragma once

#include <map>
#include <string>
#include <vector>

#include "memory/managedobject.h"
#include "memory/ptr.h"

namespace es {

class Class;
class Esther;

template <class, class>
class Map;

class Object : public ManagedObject {
    Class *objectClass;
    Map<uint32_t, Object *> *attributes;

public:
    Object(Ptr<Class> objectClass);

    virtual ~Object();

    Ptr<Class> getClass() const;
    void setClass(Ptr<Class> objectClass);

    bool hasAttribute(Esther *esther, const std::string &name) const;
    Ptr<Object> getAttribute(Esther *esther, const std::string &name) const;
    void setAttribute(Esther *esther, const std::string &name, Ptr<Object> value);

    virtual Ptr<Object> get(Esther *esther, const std::string &name) const;

    bool is(Ptr<Class> _class) const;

    virtual std::string toString() const;

    virtual bool isTrue() const;

    Ptr<Object> call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args);
    Ptr<Object> call(Esther *esther, Ptr<Object> f, const std::vector<Ptr<Object>> &args);
    Ptr<Object> call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args, Ptr<Class> expectedReturnClass);

    Ptr<Object> callIfFound(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args);

    virtual bool equals(Ptr<Object> object) const;
    virtual uint32_t hash() const;

    void finalize() override;
    void mapOnReferences(void (*f)(ManagedObject *&)) override;
    int getSize() const override;
};
}
