#include "expressiontest.h"

#include "expression/expression.h"
#include "variant/variant.h"

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
        expr = Expression::AttributeAssignment(Expression::Literal("pi"), Expression::Literal(3.14));
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
        fail();
    }).should.be.ok();

    $("Constant", [=]() {
        expr = Expression::Constant(runtime.getTrue());
        return expr->eval(&context)->toString();
    }).should.be = "true";

    $("ContextCall", [=]() {
        fail();
    }).should.be.ok();

    $("ContextResolution", [=]() {
        fail();
    }).should.be.ok();

    $("Empty", [=]() {
        expr = Expression::Empty();
        return expr->eval(&context)->toString();
    }).should.be = "null";

    $("Here", [=]() {
        Object *here = runtime.createObject();
        context.setHere(here);
        expr = Expression::Here();
        return expr->eval(&context) == here;
    }).should.be = true;

    $("Identifier", [=]() {
        fail();
    }).should.be.ok();

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
        fail();
    }).should.be.ok();

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
        Object *self = runtime.createObject();
        context.setSelf(self);
        expr = Expression::Self();
        return expr->eval(&context) == self;
    }).should.be = true;
}
