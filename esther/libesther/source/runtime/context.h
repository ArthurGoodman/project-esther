#pragma once

#include <string>
#include <list>

#include "memory/managedobject.h"
#include "memory/pointer.h"

class Object;
class Esther;

class Context : public ManagedObject {
    Esther *esther;
    Pointer<Context> parent;
    Pointer<Object> self, here;

    //    std::list<Pointer<Context>> children;

public:
    Context(Esther *esther);
    virtual ~Context();

    Pointer<Object> getSelf() const;
    void setSelf(Pointer<Object> self);

    Pointer<Object> getHere() const;
    void setHere(Pointer<Object> here);

    bool hasLocal(const std::string &name) const;
    Pointer<Object> getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Pointer<Object> value);

    Pointer<Object> get(const std::string &name) const;
    bool set(const std::string &name, Pointer<Object> value);

    Pointer<Context> childContext();
    Pointer<Context> childContext(Pointer<Object> self, Pointer<Object> here);

    virtual int getSize() const;

private:
    Context(Pointer<Object> self, Pointer<Object> here, Pointer<Context> parent);
};
