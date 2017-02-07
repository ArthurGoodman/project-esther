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
    void setSelf(Object *self);

    Object *getHere() const;
    void setHere(Object *here);

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(Esther *esther, const std::string &name) const;
    bool set(const std::string &name, Object *value);

    Context *childContext(Object *self, Object *here);

private:
    Context(Object *self, Object *here, Context *parent);
};
}
