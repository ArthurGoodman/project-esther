#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
    friend class Runtime;

public:
    Object *createObject(Class *objectClass);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    ObjectClass(Runtime *runtime);
};
