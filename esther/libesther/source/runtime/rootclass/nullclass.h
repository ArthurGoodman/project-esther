#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
    friend class Runtime;

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    NullClass(Runtime *runtime);
};
