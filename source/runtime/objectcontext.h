#pragma once
#include "common.h"

#include "context.h"

class ObjectContext : public Context {
public:
    ObjectContext(IObject *currentSelf, Class *currentClass, Context *parent, int modifiers);
    ObjectContext();

    bool hasLocal(string name);
    IObject *getLocal(string name);
    void setLocal(string name, IObject *value);

    bool hasId(string name);
    IObject *getId(string name);
    bool setId(string name, IObject *value);

    IObject *clone();
};
