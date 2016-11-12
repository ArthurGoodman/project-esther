#pragma once

#include "rootclass.h"

class ValueObject;

class FloatClass : public RootClass {
    friend class Runtime;

public:
    ValueObject *createFloat(double value);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    FloatClass(Runtime *runtime);
};
