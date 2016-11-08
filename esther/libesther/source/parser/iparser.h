#pragma once

#include <list>

#include "common.h"

class Expression;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(const Tokens &tokens) = 0;
};
