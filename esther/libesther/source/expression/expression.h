#pragma once

#include <list>

#include "common/position.h"
#include "runtime/object.h"

class Variant;
class Context;

class Expression {
    Position position;

public:
    static Expression *And(Expression *self, Expression *arg);
    static Expression *AttributeAssignment();
    static Expression *Block();
    static Expression *Constant(Object *value);
    static Expression *ContextResolution();
    static Expression *Empty();
    static Expression *Here();
    static Expression *If();
    static Expression *Literal(const Variant &value);
    static Expression *LocalAssignment();
    static Expression *Loop();
    static Expression *Not();
    static Expression *Or(Expression *self, Expression *arg);
    static Expression *Self();

    virtual ~Expression();

    Object *eval(Context *context);

    virtual Object *exec(Context *context) = 0;

    Position getPosition();
    void setPosition(Position position);
};
