#pragma once

class IObject;
class Pattern;
class Expression;
class Context;

class Case {
    Pattern *pattern;
    Expression *body;

public:
    Case(Pattern *pattern, Expression *body);

    IObject *match(IObject *object, Context *context);
};
