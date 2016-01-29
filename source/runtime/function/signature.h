#pragma once

#include <list>

#include "object.h"

class Class;
class Parameter;

class Signature : public Object {
    Class *returnClass;
    std::list<Parameter *> params;
    bool variadic;

public:
    Signature();
    Signature(Class *returnClass, std::list<Class *> paramsClasses, bool variadic = false);
    Signature(const std::string &returnClassName, std::list<std::string> paramsClassesNames, bool variadic = false);
    Signature(Class *returnClass, std::list<Parameter *> params, bool variadic = false);

    virtual bool accepts(Tuple *args);
    virtual void apply(Tuple *args);
    bool check(Tuple *args);

    virtual Tuple *convert(Tuple *args);
    IObject *convertReturnValue(IObject *value);

    virtual bool equals(Signature *other);
    virtual bool weakEquals(Signature *other);

    std::list<std::string> paramsNames();

    virtual IObject *clone();
};
