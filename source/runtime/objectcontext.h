#pragma once

#include "context.h"

class ObjectContext : public Context {
public:
    ObjectContext(IObject *currentSelf, Class *currentClass, Context *parent, int modifiers);
    ObjectContext();

    bool hasLocal(const std::string &name);
    IObject *getLocal(const std::string &name);
    void setLocal(const std::string &name, IObject *value);

    bool hasId(const std::string &name);
    IObject *getId(const std::string &name);
    bool setId(const std::string &name, IObject *value);

    IObject *clone();
};
