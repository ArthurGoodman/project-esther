#pragma once

#include "class.h"

class NullClass : public Class {
    friend class ClassClass;

public:
    Object *createNull();

protected:
    Object *createNewInstance();

private:
    NullClass(Class *objectClass);
};
