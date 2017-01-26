#pragma once

#include <string>
#include <list>

class Object;
class Esther;

class Context {
    Esther *runtime;
    Context *parent;
    Object *self, *here;

    std::list<Context *> children;

public:
    Context(Esther *runtime);
    virtual ~Context();

    Object *getSelf() const;
    void setSelf(Object *self);

    Object *getHere() const;
    void setHere(Object *here);

    Esther *getRuntime() const;

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;
    bool set(const std::string &name, Object *value);

    Context *childContext();
    Context *childContext(Object *self, Object *here);

private:
    Context(Object *self, Object *here, Context *parent);
};
