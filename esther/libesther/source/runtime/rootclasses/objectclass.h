#pragma once

#include "class.h"

class ObjectClass : public Class {
    friend class Runtime;

private:
    ObjectClass(Class *objectClass);
};
