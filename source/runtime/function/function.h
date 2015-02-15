#pragma once
#include "common.h"

#include "object.h"

class Tuple;
class Context;
class Block;

class Function : public Object {
protected:
    string name;
    Context *context;
    list<string> params;
    Block *body;

    Function(string className, string name, Context *context, list<string> params, Block *body);

public:
    Function(string name, Context *context, list<string> params, Block *body);

    string getName();

    virtual Object *invoke(Object *self, Tuple *args);

    virtual string toString();
};
