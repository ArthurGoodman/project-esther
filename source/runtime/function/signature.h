#pragma once
#include "common.h"

#include "object.h"

class Class;

class Signature : public Object {
    Class *returnClass;
    list<Class *> argsClasses;

public:
    Signature();
    Signature(Class *returnClass, list<Class *> argsClasses);
    Signature(string returnClassName, list<string> argsClassesNames);

    bool accepts(Tuple *args);
    Tuple *convert(Tuple *args);

    bool equals(Object *other);
};
