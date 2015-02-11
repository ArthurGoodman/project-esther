#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Tuple;
class Context;
class FunctionBody;

class Function : public Object {
protected:
    string name;
    Context *context;
    list<string> params;
    FunctionBody *body;

    Function(string className, string name, Context *context, list<string> params, FunctionBody *body);

public:
    Function(string name, Context *context, list<string> params, FunctionBody *body);

    virtual Object *invoke(Object *self, Tuple *args);

//    virtual string toString();
};
}
