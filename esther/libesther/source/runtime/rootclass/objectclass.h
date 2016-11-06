#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
    friend class Runtime;

protected:
    void setupMethods();

private:
    ObjectClass(Runtime *runtime, Class *objectClass);
};
