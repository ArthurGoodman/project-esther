#pragma once

#include "class.h"

class ObjectClass : public Class {
    friend class ClassClass;

private:
    ObjectClass(Class *objectClass);
};
