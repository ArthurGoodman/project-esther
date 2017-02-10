#pragma once

#include <string>
#include <list>

#include "memory/managedobject.h"

namespace es {

class Object;
class Esther;

class Context : public ManagedObject {
    Context *parent;
    Object *self, *here;

public:
    Context(Esther *esther);

    Object *getSelf() const;
    void setSelf(Object *volatile self);

    Object *getHere() const;
    void setHere(Object *volatile here);

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *volatile value);

    Object *get(Esther *esther, const std::string &name) const;
    bool set(const std::string &name, Object *volatile value);

    Context *childContext(Object *volatile self, Object *volatile here);

    void mapOnReferences(void (*f)(ManagedObject *&)) override;

private:
    Context(Object *volatile self, Object *volatile here, Context *volatile parent);
};
}
