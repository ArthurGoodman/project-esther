#pragma once

#include <list>

#include "common.h"

class Expression;

class IParser {
public:
    virtual ~IParser();
    virtual Expression *parse(Tokens &tokens) = 0;
};
