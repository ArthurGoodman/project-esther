#pragma once

#include <string>

class Object;
class Runtime;

class Context {
    Object *self, *here;
    Runtime *runtime;
    Context *parent;

public:
    Context(Runtime *runtime);

    Object *getSelf() const;
    void setSelf(Object *self);

    Object *getHere() const;
    void setHere(Object *here);

    Runtime *getRuntime() const;

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;
    std::pair<Object *, Object *> getWithSource(const std::string &name) const;

    void clear();

    Context *childContext(Object *self, Object *here);

private:
    Context(Object *self, Object *here, Context *parent);
};
