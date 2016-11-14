#pragma once

#include <string>
#include <list>

class Object;
class Runtime;

class Context {
    std::list<Object *> selves, heres;
    Runtime *runtime;
    Context *parent;

    std::list<Context *> children;

public:
    Context(Runtime *runtime);
    virtual ~Context();

    Object *getSelf() const;
    void setSelf(Object *self);

    Object *getHere() const;
    void setHere(Object *here);

    void pushSelf(Object *self);
    void popSelf();

    void pushHere(Object *here);
    void popHere();

    Runtime *getRuntime() const;

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;
    std::pair<Object *, Object *> getWithSource(const std::string &name) const;

    Context *childContext();
    Context *childContext(Object *self, Object *here);

private:
    Context(Object *self, Object *here, Context *parent);
};
