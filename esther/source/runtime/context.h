#pragma once

#include "object.h"

class Context {
    Object *self;
    std::map<std::string, Object *> locals;
    Context *parent;

public:
    Context();
    Context(Object *self, Context *parent);

    Object *getSelf() const;
    void setSelf(Object *self);

    bool hasLocal(const std::string &name) const;
    Object *getLocal(const std::string &name) const;
    void setLocal(const std::string &name, Object *value);

    Object *get(const std::string &name) const;

    void clear();
};
