#pragma once
#include "common.h"

#include "object.h"

class Context : public Object {
protected:
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
    virtual void setLocal(string name, Object *value);

    virtual bool hasId(string name);
    virtual Object *getId(string name);
    virtual bool setId(string name, Object *value);

//    Context *childContext();
//    Context *childContext(Object *self);
//    Context *childContext(Object *self, Class *_class);

    Context *childContext(Object *currentSelf, Class *currentClass);
    Context *childContext(Object *currentSelf);
    Context *childContext();

    Context *objectChildContext(Object *currentSelf, Class *currentClass);
    Context *objectChildContext(Object *currentSelf);
    Context *objectChildContext();

    bool hasParent();
    Context *getParent();
};
