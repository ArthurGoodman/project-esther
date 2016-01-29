#pragma once

#include <list>

#include "object.h"

class Tuple;
class Context;
class Signature;
class Block;
class FunctionFeature;

class Function : public Object {
protected:
    std::string name;
    Context *context;
    Signature *signature;
    Block *body;

    std::list<FunctionFeature *> features;

    Function(const std::string &className, const std::string &name, Context *context, Signature *signature, Block *body);

public:
    Function(const std::string &name, Context *context, Signature *signature, Block *body);

    std::string getName();
    Signature *getSignature();
    Block *getBody();

    virtual IObject *invoke(IObject *self, Tuple *args);
    virtual IObject *execute(IObject *self, Tuple *args);

    virtual std::string toString();

    virtual IObject *clone();

protected:
    void addFeature(FunctionFeature *feature);
};
