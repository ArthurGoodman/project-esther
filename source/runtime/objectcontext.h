#pragma once
#include "common.h"

#include "context.h"

class ObjectContext : public Context {
public:
    ObjectContext(Object *currentSelf, Class *currentClass, Context *parent, int modifiers);
    ObjectContext();

    bool hasLocal(string name);
    Object *getLocal(string name);
    void setLocal(string name, Object *value);

    bool hasId(string name);
    Object *getId(string name);
    bool setId(string name, Object *value);

    Object *clone();
};
