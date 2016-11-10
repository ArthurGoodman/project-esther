#include "expressiontest.h"

#include "expression/expression.h"
#include "variant/variant.h"
#include "runtime/valueobject.h"
#include "runtime/function.h"

ExpressionTest::ExpressionTest()
    : TestSet("expressions"), context(&runtime), expr(nullptr) {
    defineTests();
}

void ExpressionTest::preTest() {
    runtime.initialize();

    context.setSelf(runtime.getMainObject());
    context.setHere(runtime.getMainObject());
}

void ExpressionTest::postTest() {
    delete expr;
    expr = nullptr;
}

void ExpressionTest::defineTests() {
    $("And -> 1", [=]() {
        expr = Expression::And(Expression::Empty(), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "null";

    $("And -> 2", [=]() {
        expr = Expression::And(Expression::Literal(1), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "2";

    $("AttributeAssignment", [=]() {
        expr = Expression::AttributeAssignment(Expression::Self(), Expression::Literal("pi"), Expression::Literal(3.14));
        expr->eval(&context);
        return context.getSelf()->getAttribute("pi")->toString();
    }).should.be = "3.14";

    $("Block", [=]() {
        std::list<Expression *> nodes;

        nodes << Expression::Literal(1);
        nodes << Expression::Literal(2);
        nodes << Expression::Literal(3);

        expr = Expression::Block(nodes);

        return expr->eval(&context)->toString();
    }).should.be = "3";

    $("Call", [=]() {
        context.setSelf(runtime.createInteger(3));
        context.setLocal("f", runtime.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

        Context *childContext = context.childContext(runtime.createInteger(4), runtime.createObject());

        expr = Expression::Call(nullptr, Expression::Literal("f"), {});

        Object *value = expr->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3";

    $("Constant", [=]() {
        expr = Expression::Constant(runtime.getTrue());
        return expr->eval(&context)->toString();
    }).should.be = "true";

    $("DirectCall", [=]() {
        expr = Expression::DirectCall(Expression::Literal(4), "+", {Expression::Literal(5)});
        return expr->eval(&context)->toString();
    }).should.be = "9";

    $("DynamicCall", [=]() {
        context.setSelf(runtime.createInteger(3));
        context.setLocal("f", runtime.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

        Context *childContext = context.childContext(runtime.createInteger(4), runtime.createObject());

        expr = Expression::DynamicCall(Expression::Identifier(Expression::Literal("f")), {});

        Object *value = expr->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "4";

    $("ContextResolution", [=]() {
        Context *childContext = context.childContext(runtime.createInteger(3), runtime.createObject());
        expr = Expression::ContextResolution(Expression::Literal(4), Expression::Self(), childContext);

        Object *value = expr->eval(&context);
        delete childContext;
        return value->toString();
    }).should.be = "4";

    $("Empty", [=]() {
        expr = Expression::Empty();
        return expr->eval(&context)->toString();
    }).should.be = "null";

    $("Here", [=]() {
        expr = Expression::Here();
        return expr->eval(&context) == context.getHere();
    }).should.be = true;

    $("Identifier // local", [=]() {
        context.setLocal("pi", runtime.createFloat(3.14));

        expr = Expression::Identifier(Expression::Literal("pi"));

        Context *childContext = context.childContext(runtime.createObject(), runtime.createObject());
        Object *value = expr->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3.14";

    $("Identifier // attribute", [=]() {
        context.getSelf()->setAttribute("pi", runtime.createFloat(3.14));

        expr = Expression::Identifier(Expression::Literal("pi"));

        Context *childContext = context.childContext(runtime.createObject(), runtime.createObject());
        Object *value = expr->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3.14";

    $("Identifier // undefined", [=]() {
        expr = Expression::Identifier(Expression::Literal("id"));
        return expr->eval(&context)->toString();
    }).should_not.be.ok();

    $("If -> 1", [=]() {
        expr = Expression::If(Expression::Constant(runtime.getTrue()), Expression::Literal(1), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "1";

    $("If -> 2", [=]() {
        expr = Expression::If(Expression::Constant(runtime.getFalse()), Expression::Literal(1), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "2";

    $("Literal", [=]() {
        expr = Expression::Literal(3.14);
        return expr->eval(&context)->toString();
    }).should.be = "3.14";

    $("LocalAssignment", [=]() {
        expr = Expression::LocalAssignment(Expression::Literal("pi"), Expression::Literal(3.14));
        expr->eval(&context);
        return context.getLocal("pi")->toString();
    }).should.be = "3.14";

    $("Loop", [=]() {
        expr = Expression::Block({Expression::LocalAssignment(Expression::Literal("i"), Expression::Literal(0)),
                                  Expression::Loop(Expression::DirectCall(Expression::Identifier(Expression::Literal("i")), "<", {Expression::Literal(10)}),
                                                   Expression::LocalAssignment(Expression::Literal("i"), Expression::DirectCall(Expression::Identifier(Expression::Literal("i")), "+", {Expression::Literal(1)})))});

        return expr->eval(&context)->toString();
    }).should.be = "10";

    $("Not", [=]() {
        expr = Expression::Not(Expression::Constant(runtime.getTrue()));
        return expr->eval(&context)->toString();
    }).should.be = "false";

    $("Or -> 1", [=]() {
        expr = Expression::Or(Expression::Literal(1), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "1";

    $("Or -> 2", [=]() {
        expr = Expression::Or(Expression::Empty(), Expression::Literal(2));
        return expr->eval(&context)->toString();
    }).should.be = "2";

    $("Self", [=]() {
        expr = Expression::Self();
        return expr->eval(&context) == context.getSelf();
    }).should.be = true;
}
