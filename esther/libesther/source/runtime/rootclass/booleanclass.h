#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
    friend class Runtime;

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    BooleanClass(Runtime *runtime, Class *objectClass);
};
