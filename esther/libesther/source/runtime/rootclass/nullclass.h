#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
    friend class Runtime;

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    NullClass(Runtime *runtime, Class *objectClass);
};
