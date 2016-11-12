#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
    friend class Runtime;

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    BooleanClass(Runtime *runtime);
};
