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
    //~Context();

    Object *getCurrentSelf();
    Class *getCurrentClass();

    bool isObjectContext();

    bool hasLocal(string name);
    Object *getLocal(string name);
    void setLocalOrAttribute(string name, Object *value);
    void setLocal(string name, Object *value);

    bool hasId(string name);
    Object *getId(string name);
    bool setId(string name, Object *value);

    Context *childContext();
    Context *childContext(Object *self);
    Context *childContext(Object *self, Class *_class);

    bool hasParent();
    Context *getParent();
};
}
