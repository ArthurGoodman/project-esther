#pragma once

#include "rootclass.h"

class NumericClass : public RootClass {
    friend class Runtime;

protected:
    void setupMethods();

private:
    NumericClass(Runtime *runtime);
};
