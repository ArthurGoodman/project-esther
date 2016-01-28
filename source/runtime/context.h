#pragma once
#include "common.h"

#include "object.h"

class Method;

class Context : public Object {
protected:
    IObject *currentSelf;
    Class *currentClass;
    Context *parent;

    int modifiers;

    map<string, IObject *> locals;

    Context(IObject *currentSelf, Class *currentClass, Context *parent, int modifiers);

public:
    const static int StaticModifier = 0x1;

    Context(IObject *currentSelf, Class *currentClass, Context *parent = 0);
    Context(IObject *currentSelf, Context *parent = 0);
    Context();

    IObject *getCurrentSelf();
    Class *getCurrentClass();

    //    bool isObjectContext();

    virtual bool hasLocal(string name);
    virtual IObject *getLocal(string name);
    virtual void setLocal(string name, IObject *value);

    virtual bool hasId(string name);
    virtual IObject *getId(string name);
    virtual bool setId(string name, IObject *value);

    Context *childContext(IObject *currentSelf, Class *currentClass);
    Context *childContext(IObject *currentSelf);
    Context *childContext();

    Context *objectChildContext(IObject *currentSelf, Class *currentClass);
    Context *objectChildContext(IObject *currentSelf);
    Context *objectChildContext();

    bool hasParent();
    Context *getParent();

    void setModifier(int modifier, bool state);
    int getModifier(int modifier);

    IObject *getSelfForMethod(Method *method);

    virtual IObject *clone();
};
