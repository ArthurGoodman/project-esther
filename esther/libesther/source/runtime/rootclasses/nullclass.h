#pragma once

#include "class.h"

class NullClass : public Class {
    friend class Runtime;

protected:
    Object *createNewInstance();

private:
    NullClass(Class *objectClass);
};
