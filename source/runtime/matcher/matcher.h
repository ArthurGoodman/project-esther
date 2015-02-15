#pragma once
#include "common.h"

#include "function.h"

class Case;

class Matcher : public Function {
public:
    Matcher(list<Case *> cases);
};
