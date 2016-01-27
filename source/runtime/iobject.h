#pragma once
#include "common.h"

class IClass;
class ITuple;

class IObject {
public:
    virtual IObject *call(string name, ITuple *args) = 0;

    virtual bool is(IClass *_class) = 0;
    virtual bool as(IClass *_class) = 0;

    virtual bool isTrue() = 0;
    virtual bool isFalse() = 0;

    virtual string immediateToString() = 0;

    virtual IObject *clone() = 0;
};
