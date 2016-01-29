#pragma once

#include "function.h"

class Case;

class Matcher : public Function {
public:
    Matcher(std::list<Case *> cases);
};
