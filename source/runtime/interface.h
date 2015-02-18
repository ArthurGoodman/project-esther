#pragma once
#include "common.h"

#include "class.h"

class Interface : public Class
{
public:
    Interface(string name);

    Object *newInstance();

    string toString();
};
