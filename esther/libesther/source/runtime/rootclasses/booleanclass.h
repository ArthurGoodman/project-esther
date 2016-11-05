#pragma once

#include "class.h"

class BooleanClass : public Class {
    friend class ClassClass;

public:
    Object *createTrue();
    Object *createFalse();

protected:
    Object *createNewInstance();

private:
    BooleanClass(Class *objectClass);
};
