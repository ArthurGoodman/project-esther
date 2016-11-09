#pragma once

#include <string>
#include <list>

class Object;
class Runtime;

class Context {
    Object *self, *here;
    Runtime *runtime;
    Context *parent;

    std::list<Context *> children;

public:
    Context(Runtime *runtime);
    virtual ~Context();

    Object *getSelf() const;
    virtual void setSelf(Object *self);

    Object *getHere() const;
    void setHere(Object *here);

    Runtime *getRuntime() const;

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;
    std::pair<Object *, Object *> getWithSource(const std::string &name) const;

    virtual void clear();

    Context *childContext(Object *self, Object *here);
    Context *childContext(Object *here);
    Context *objectChildContext(Object *self, Object *here);
    Context *objectChildContext();

protected:
    Context(Object *self, Object *here, Context *parent);
};
