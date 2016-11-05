#include "expressiontest.h"

#include "runtime/context.h"
#include "expression/expression.h"
#include "variant/variant.h"

ExpressionTest::ExpressionTest()
    : TestSet("expressions"), context(nullptr) {
    defineTests();
}

void ExpressionTest::preTest() {
    runtime.initialize();
    context = new Context(&runtime);
    expr = nullptr;
}

void ExpressionTest::postTest() {
    delete expr;
    expr = nullptr;

    delete context;
    context = nullptr;

    runtime.release();
}

void ExpressionTest::defineTests() {
    $("And -> 1", [=]() {
        expr = Expression::And(Expression::Empty(), Expression::Literal(2));
        return expr->eval(context)->toString();
    }).should.be = "null";

    $("And -> 2", [=]() {
        expr = Expression::And(Expression::Literal(1), Expression::Literal(2));
        return expr->eval(context)->toString();
    }).should.be = "2";

    $("AttributeAssignment", [=]() { fail(); })
        .should.be.ok();

    $("Block", [=]() { fail(); })
        .should.be.ok();

    $("Call", [=]() { fail(); })
        .should.be.ok();

    $("Constant", [=]() {
        expr = Expression::Constant(runtime.getTrue());
        return expr->eval(context)->toString();
    }).should.be = "true";

    $("Empty", [=]() { fail(); })
        .should.be.ok();

    $("Here", [=]() { fail(); })
        .should.be.ok();

    $("Identifier", [=]() { fail(); })
        .should.be.ok();

    $("If", [=]() { fail(); })
        .should.be.ok();

    $("Literal", [=]() {
        expr = Expression::Literal(3.14);
        return expr->eval(context)->toString();
    }).should.be = "3.14";

    $("LocalAssignment", [=]() { fail(); })
        .should.be.ok();

    $("Loop", [=]() { fail(); })
        .should.be.ok();

    $("Not", [=]() { fail(); })
        .should.be.ok();

    $("Or -> 1", [=]() {
        expr = Expression::Or(Expression::Literal(1), Expression::Literal(2));
        return expr->eval(context)->toString();
    }).should.be = "1";

    $("Or -> 2", [=]() {
        expr = Expression::Or(Expression::Empty(), Expression::Literal(2));
        return expr->eval(context)->toString();
    }).should.be = "2";

    $("Self", [=]() { fail(); })
        .should.be.ok();
}
