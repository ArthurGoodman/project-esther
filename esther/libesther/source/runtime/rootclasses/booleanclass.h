#pragma once

#include "class.h"

class BooleanClass : public Class {
    friend class Runtime;

protected:
    Object *createNewInstance();

private:
    BooleanClass(Class *objectClass);
};
