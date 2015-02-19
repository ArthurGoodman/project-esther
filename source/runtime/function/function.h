#pragma once
#include "common.h"

#include "object.h"

class Tuple;
class Context;
class Signature;
class Block;

class Function : public Object {
protected:
    string name;
    Context *context;
    Signature *signature;
    list<string> params;
    Block *body;

    Function(string className, string name, Context *context, Signature *signature, list<string> params, Block *body);

public:
    Function(string name, Context *context, Signature *signature, list<string> params, Block *body);

    string getName();
    Signature *getSignature();

    virtual Object *invoke(Object *self, Tuple *args);

    virtual string toString();

protected:
    virtual void check(Object *self, Tuple *args);
};
