#pragma once

#include <string>

class Object;
class Runtime;

class Context {
    Object *self, *here;
    Runtime *runtime;
    Context *parent;

public:
    //Context();
    Context(Object *self, Context *parent);

    Object *getSelf() const;
    void setSelf(Object *self);

    Object *getHere() const;

    Runtime *getRuntime() const;

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;

    void clear();
};
