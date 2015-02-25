#pragma once
#include "common.h"

#include "object.h"

class Class;
class Parameter;

class Signature : public Object {
    Class *returnClass;
    list<Parameter *> params;

public:
    Signature();
    Signature(Class *returnClass, list<Class *> paramsClasses);
    Signature(string returnClassName, list<string> paramsClassesNames);
    Signature(Class *returnClass, list<Parameter *> params);

    bool accepts(Tuple *args);
    bool check(Tuple *args);

    Tuple *convert(Tuple *args);

    bool equals(Signature *other);

    list<string> paramsNames();
};
