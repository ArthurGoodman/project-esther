#include "expressiontest.h"

#include <expression/expression.h>
#include <variant/variant.h>
#include <runtime/valueobject.h>
#include <runtime/function.h>

ExpressionTest::ExpressionTest()
    : TestSet("expressions")
    , context(&esther)
    , e(nullptr) {
    defineTests();
}

void ExpressionTest::preTest() {
    //    esther.initialize();

    //    context.setSelf(esther.getMainObject());
    //    context.setHere(esther.getMainObject());
}

void ExpressionTest::postTest() {
    //    delete e;
    //    e = nullptr;
}

void ExpressionTest::defineTests() {
    //    $("And -> 1", [=]() {
    //        e = Expression::And(Expression::Empty(), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "null";

    //    $("And -> 2", [=]() {
    //        e = Expression::And(Expression::Literal(1), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "2";

    //    $("Assignment", [=]() {
    //        fail();
    //    }).should.be.ok();

    //    $("AttributeAssignment", [=]() {
    //        e = Expression::AttributeAssignment(Expression::Self(), "pi", Expression::Literal(3.14));
    //        e->eval(&context);
    //        return context.getSelf()->getAttribute("pi")->toString();
    //    }).should.be = "3.14";

    //    $("Block", [=]() {
    //        std::list<Expression *> nodes;

    //        nodes << Expression::Literal(1);
    //        nodes << Expression::Literal(2);
    //        nodes << Expression::Literal(3);

    //        e = Expression::Block(nodes);

    //        return e->eval(&context)->toString();
    //    }).should.be = "3";

    //    $("Call", [=]() {
    //        context.setSelf(esther.createInteger(3));
    //        context.setLocal("f", esther.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

    //        Ptr<Context> childContext = context.childContext(esther.createInteger(4), esther.createObject());

    //        e = Expression::Call("f", {});

    //        Object *value = e->eval(childContext);
    //        delete childContext;
    //        return value->toString();
    //    }).should.be = "4";

    //    $("ClassDefinition", [=]() {
    //        fail();
    //    }).should.be.ok();

    //    $("Constant", [=]() {
    //        e = Expression::Constant(esther.getTrue());
    //        return e->eval(&context)->toString();
    //    }).should.be = "true";

    //    $("ContextCall", [=]() {
    //        fail();
    //    }).should.be.ok();

    //    $("ContextResolution", [=]() {
    //        e = Expression::ContextResolution(Expression::Literal(4), Expression::Self());
    //        return e->eval(&context)->toString();
    //    }).should.be = "4";

    //    $("DirectCall", [=]() {
    //        e = Expression::DirectCall(Expression::Literal(4), "+", { Expression::Literal(5) });
    //        return e->eval(&context)->toString();
    //    }).should.be = "9";

    //    $("DynamicCall", [=]() {
    //        context.setSelf(esther.createInteger(3));
    //        context.setLocal("f", esther.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

    //        Ptr<Context> childContext = context.childContext(esther.createInteger(4), esther.createObject());

    //        e = Expression::DynamicCall(Expression::Identifier("f"), {});

    //        Object *value = e->eval(childContext);
    //        delete childContext;
    //        return value->toString();
    //    }).should.be = "4";

    //    $("Empty", [=]() {
    //        e = Expression::Empty();
    //        return e->eval(&context)->toString();
    //    }).should.be = "null";

    //    $("FunctionDefinition", [=]() {
    //        fail();
    //    }).should.be.ok();

    //    $("Here", [=]() {
    //        e = Expression::Here();
    //        return e->eval(&context) == context.getHere();
    //    }).should.be = true;

    //    $("Identifier // local", [=]() {
    //        context.setLocal("pi", esther.createFloat(3.14));

    //        e = Expression::Identifier("pi");

    //        Ptr<Context> childContext = context.childContext(esther.createObject(), esther.createObject());
    //        Object *value = e->eval(childContext);
    //        delete childContext;
    //        return value->toString();
    //    }).should.be = "3.14";

    //    $("Identifier // attribute", [=]() {
    //        context.getSelf()->setAttribute("pi", esther.createFloat(3.14));

    //        e = Expression::Identifier("pi");

    //        Ptr<Context> childContext = context.childContext(esther.createObject(), esther.createObject());
    //        Object *value = e->eval(childContext);
    //        delete childContext;
    //        return value->toString();
    //    }).should.be = "3.14";

    //    $("Identifier // undefined", [=]() {
    //        e = Expression::Identifier("id");
    //        return e->eval(&context)->toString();
    //    }).should_not.be.ok();

    //    $("If -> 1", [=]() {
    //        e = Expression::If(Expression::Constant(esther.getTrue()), Expression::Literal(1), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "1";

    //    $("If -> 2", [=]() {
    //        e = Expression::If(Expression::Constant(esther.getFalse()), Expression::Literal(1), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "2";

    //    $("Literal", [=]() {
    //        e = Expression::Literal(3.14);
    //        return e->eval(&context)->toString();
    //    }).should.be = "3.14";

    //    $("LocalAssignment", [=]() {
    //        e = Expression::LocalAssignment("pi", Expression::Literal(3.14));
    //        e->eval(&context);
    //        return context.getLocal("pi")->toString();
    //    }).should.be = "3.14";

    //    $("Loop", [=]() {
    //        e = Expression::Block({ Expression::Assignment("i", Expression::Literal(0)),
    //                                Expression::Loop(Expression::DirectCall(Expression::Identifier("i"), "<", { Expression::Literal(10) }),
    //                                                 Expression::Assignment("i", Expression::DirectCall(Expression::Identifier("i"), "+", { Expression::Literal(1) }))) });

    //        return e->eval(&context)->toString();
    //    }).should.be = "10";

    //    $("Not", [=]() {
    //        e = Expression::Not(Expression::Constant(esther.getTrue()));
    //        return e->eval(&context)->toString();
    //    }).should.be = "false";

    //    $("Or -> 1", [=]() {
    //        e = Expression::Or(Expression::Literal(1), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "1";

    //    $("Or -> 2", [=]() {
    //        e = Expression::Or(Expression::Empty(), Expression::Literal(2));
    //        return e->eval(&context)->toString();
    //    }).should.be = "2";

    //    $("Self", [=]() {
    //        e = Expression::Self();
    //        return e->eval(&context) == context.getSelf();
    //    }).should.be = true;
}
