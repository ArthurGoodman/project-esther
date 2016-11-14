#pragma once

#include "context.h"

class ObjectContext : public Context {
    friend class Context;

public:
    void pushSelf(Object *self);
    void popSelf();

    void pushHere(Object *here);
    void popHere();

private:
    ObjectContext(Object *self, Object *here, Context *parent);
};
