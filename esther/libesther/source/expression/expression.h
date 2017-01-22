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
    static Expression *Assignment(const std::string &name, Expression *value);
    static Expression *AttributeAssignment(Expression *self, const std::string &name, Expression *value);
    static Expression *Attribute(Expression *self, const std::string &name);
    static Expression *Block(const std::list<Expression *> &nodes);
    static Expression *Call(const std::string &name, const std::list<Expression *> &args);
    static Expression *ClassDefinition(const std::string &name, Expression *superclass, Expression *body = nullptr);
    static Expression *Constant(Object *value);
    static Expression *ContextResolution(Expression *self, Expression *body);
    static Expression *ContextCall(Expression *self, Expression *body, const std::list<Expression *> &args);
    static Expression *DirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args);
    static Expression *DynamicCall(Expression *body, const std::list<Expression *> &args);
    static Expression *Empty();
    static Expression *FunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body);
    static Expression *Here();
    static Expression *Identifier(const std::string &name);
    static Expression *If(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *Literal(const Variant &value);
    static Expression *LocalAssignment(const std::string &name, Expression *value);
    static Expression *Loop(Expression *condition, Expression *body);
    static Expression *Not(Expression *self);
    static Expression *Or(Expression *self, Expression *arg);
    static Expression *Self();

    virtual ~Expression();

    Object *eval(Context *context);

    Position getPosition() const;
    void setPosition(Position position);

protected:
    virtual Object *exec(Context *context) = 0;
};
