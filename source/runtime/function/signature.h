#pragma once
#include "common.h"

#include "object.h"

class Class;
class Parameter;

class Signature : public Object {
    Class *returnClass;
    list<Parameter *> params;
    bool variadic;

public:
    Signature();
    Signature(Class *returnClass, list<Class *> paramsClasses, bool variadic = false);
    Signature(string returnClassName, list<string> paramsClassesNames, bool variadic = false);
    Signature(Class *returnClass, list<Parameter *> params, bool variadic = false);

    virtual bool accepts(Tuple *args);
    bool check(Tuple *args);

    Tuple *convert(Tuple *args);
    Object *convertReturnValue(Object *value);

    bool equals(Signature *other);

    list<string> paramsNames();
};
