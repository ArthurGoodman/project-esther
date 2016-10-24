#pragma once

#include <list>

#include "object.h"
#include "position.h"

class Variant;
class Context;

class Expression {
    Position position;

public:
    static Expression *And();
    static Expression *AttributeAssignment();
    static Expression *Block();
    static Expression *Constant();
    static Expression *ContextResolution();
    static Expression *Empty();
    static Expression *Here();
    static Expression *If();
    static Expression *Literal();
    static Expression *LocalAssignment();
    static Expression *Loop();
    static Expression *Not();
    static Expression *Or();
    static Expression *Self();

    virtual ~Expression();

    Object *eval(Context *context);

    virtual Object *exec(Context *context) = 0;

    Position getPosition();
    void setPosition(Position position);
};
