#pragma once
#include "common.h"

class Object;
class Pattern;
class Expression;
class Context;

class Case {
    Pattern *pattern;
    Expression *body;

public:
    Case(Pattern *pattern, Expression *body);

    Object *match(Object *object, Context *context);
};
