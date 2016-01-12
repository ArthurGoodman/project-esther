#pragma once
#include "common.h"

#include "object.h"

class Method;

class Context : public Object {
protected:
    Object *currentSelf;
    Class *currentClass;
    Context *parent;

    int modifiers;

    map<string, Object *> locals;

    Context(Object *currentSelf, Class *currentClass, Context *parent, int modifiers);

public:
    const static int StaticModifier = 0x1;

    Context(Object *currentSelf, Class *currentClass, Context *parent = 0);
    Context(Object *currentSelf, Context *parent = 0);
    Context();

    Object *getCurrentSelf();
    Class *getCurrentClass();

    //    bool isObjectContext();

    virtual bool hasLocal(string name);
    virtual Object *getLocal(string name);
    virtual void setLocal(string name, Object *value);

    virtual bool hasId(string name);
    virtual Object *getId(string name);
    virtual bool setId(string name, Object *value);

    Context *childContext(Object *currentSelf, Class *currentClass);
    Context *childContext(Object *currentSelf);
    Context *childContext();

    Context *objectChildContext(Object *currentSelf, Class *currentClass);
    Context *objectChildContext(Object *currentSelf);
    Context *objectChildContext();

    bool hasParent();
    Context *getParent();

    void setModifier(int modifier, bool state);
    int getModifier(int modifier);

    Object *getSelfForMethod(Method *method);

    virtual Object *clone();
};
