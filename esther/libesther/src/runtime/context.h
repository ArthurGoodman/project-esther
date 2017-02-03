#pragma once

#include <string>
#include <list>

#include "memory/managedobject.h"
#include "memory/ptr.h"

namespace es {

class Object;
class Esther;

class Context : public ManagedObject {
    Context *parent;
    Object *self, *here;

public:
    Context(Esther *esther);

    Ptr<Object> getSelf() const;
    void setSelf(Ptr<Object> self);

    Ptr<Object> getHere() const;
    void setHere(Ptr<Object> here);

    bool hasLocal(const std::string &name) const;
    Ptr<Object> getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Ptr<Object> value);

    Ptr<Object> get(Esther *esther, const std::string &name) const;
    bool set(const std::string &name, Ptr<Object> value);

    Ptr<Context> childContext(Ptr<Object> self, Ptr<Object> here);

    void mapOnReferences(void (*f)(ManagedObject *&)) override;
    int getSize() const override;

private:
    Context(Ptr<Object> self, Ptr<Object> here, Ptr<Context> parent);
};
}
