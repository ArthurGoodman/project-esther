#pragma once

#include <list>

#include "object.h"
#include "position.h"

class Variant;
class Context;

class Expression : public Object {
    Position position;

public:
    virtual ~Expression();

    static Expression *Empty();

    static Expression *Block(std::list<Expression *> nodes);
    static Expression *List(std::list<Expression *> nodes);

    static Expression *TupleLiteral(std::list<Expression *> nodes = std::list<Expression *>());
    static Expression *Assignment(Expression *expression, Expression *value);

    static Expression *Literal(const Variant &value);
    static Expression *Constant(IObject *value);

    static Expression *Or(Expression *self, Expression *arg);
    static Expression *And(Expression *self, Expression *arg);

    static Expression *Negate(Expression *self);

    static Expression *PreDecrement(Expression *self);
    static Expression *PreIncrement(Expression *self);
    static Expression *PostDecrement(Expression *self);
    static Expression *PostIncrement(Expression *self);

    static Expression *Identifier(Expression *name, bool dynamic);
    static Expression *IdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic);

    static Expression *ParameterDefinition(Expression *type, Expression *name, Expression *value, bool dynamic);

    static Expression *Call(Expression *self, const std::string &name, std::list<Expression *> args);
    static Expression *Call(Expression *self, const std::string &name, Expression *arg);
    static Expression *Call(Expression *self, const std::string &name);

    static Expression *If(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *While(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *For(Expression *param, Expression *expression, Expression *body);
    static Expression *Do(Expression *body, Expression *condition);

    static Expression *ContextResolution(Expression *self, Expression *body);
    static Expression *ContextCall(Expression *self, Expression *body, std::list<Expression *> args);

    static Expression *ClassDefinition(Expression *name, Expression *superclass, Expression *body);

    static Expression *FunctionDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);
    static Expression *MethodDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    static Expression *Return(Expression *value);
    static Expression *Break(Expression *value);
    static Expression *Continue();

    static Expression *Self();
    static Expression *Here();

    static Expression *Static(Expression *body);
    static Expression *Include(Expression *fileName);
    static Expression *ObjectLiteral(Expression *body);

    IObject *eval(Context *context);

    virtual IObject *exec(Context *context) = 0;

    Position getPosition();
    void setPosition(Position position);
};
