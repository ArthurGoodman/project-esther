#pragma once

#include "context.h"

class ObjectContext : public Context {
    friend class Context;

public:
    void setSelf(Object *self);
    void clear();

private:
    ObjectContext(Object *self, Object *here, Context *parent);
};
