#pragma once
#include "common.h"

#include "object.h"

class Pattern;
class Expression;
class Context;

class Case : public Object {
    Pattern *pattern;
    Expression *body;
    Context *context;

public:
    Case(Pattern *pattern, Expression *body, Context *context);

    Pattern *getPattern();

    Object *match(Object *object);
};
