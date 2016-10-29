#pragma once

#include "rootclass.h"

class StringClass : public RootClass {
public:
    Object *createString(const std::string &value);

    void setupMethods();

protected:
    Object *createNewInstance();
};
