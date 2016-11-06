#pragma once

#include "rootclass.h"

class ValueObject;

class StringClass : public RootClass {
    friend class Runtime;

public:
    ValueObject *createString(const std::string &value);

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    StringClass(Runtime *runtime);
};
