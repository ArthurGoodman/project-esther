#pragma once

#include <list>

#include "common/position.h"
#include "runtime/object.h"

class Variant;
class Esther;

class Expression {
    Position position;

public:
    static Expression *And(Expression *self, Expression *arg);
    static Expression *Assignment(const std::string &name, Expression *value);
    static Expression *AttributeAssignment(Expression *self, const std::string &name, Expression *value);
    static Expression *Attribute(Expression *self, const std::string &name);
    static Expression *Block(const std::list<Expression *> &nodes);
    static Expression *Call(Expression *f, Expression *self, int args);
    static Expression *ClassDefinition(const std::string &name, Expression *superclass);
    static Expression *Constant(Pointer<Object> value);
    static Expression *ContextResolution(Expression *self, Expression *body, Expression *here = nullptr);
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
    static Expression *Pop(int count);
    static Expression *Push(Expression *arg);
    static Expression *Self();
    static Expression *Stack(int index);

    virtual ~Expression();

    Pointer<Object> eval(Esther *esther);

    Position getPosition() const;
    void setPosition(Position position);

protected:
    virtual Pointer<Object> exec(Esther *esther) = 0;
};
