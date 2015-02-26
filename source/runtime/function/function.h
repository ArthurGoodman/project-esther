#pragma once
#include "common.h"

#include "object.h"

class Tuple;
class Context;
class Signature;
class Block;
class FunctionFeature;

class Function : public Object {
protected:
    string name;
    Context *context;
    Signature *signature;
    Block *body;

    list<FunctionFeature *> features;

    Function(string className, string name, Context *context, Signature *signature, Block *body);

public:
    Function(string name, Context *context, Signature *signature, Block *body);

    string getName();
    Signature *getSignature();
    Block *getBody();

    virtual Object *invoke(Object *self, Tuple *args);
    virtual Object *execute(Object *self, Tuple *args);

    virtual string toString();

protected:
    void addFeature(FunctionFeature *feature);
};
