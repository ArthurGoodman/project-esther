#pragma once

#include "object.h"

class Function;

class Range : public Object {
    int first, second;

public:
    Range(int first, int second);

    int getFirst();
    int getSecond();

    void setFirst(int first);
    void setSecond(int second);

    void each(Function *f);

    IObject *clone();
};
