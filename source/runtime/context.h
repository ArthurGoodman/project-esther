#pragma once
#include <common.h>

#include "object.h"

namespace esther {

class Context : public Object {
    Object *currentSelf;
    Class *currentClass;
    map<string, Object *> locals;

    Context *parent;

public:
    Context(Object *currentSelf, Class *currentClass, Context *parent = 0);
    Context(Object *currentSelf, Context *parent = 0);
    Context();
    ~Context();

    Object *getCurrentSelf();
    Class *getCurrentClass();

    bool hasLocal(string name);
    void setLocal(string name, Object *value);

    bool hasId(string name);
    Object *getId(string name);
    void setId(string name, Object *value);

    Context *childContext();
    Context *childContext(Object *self);

    bool hasParent();
    Context *getParent();
};
}
