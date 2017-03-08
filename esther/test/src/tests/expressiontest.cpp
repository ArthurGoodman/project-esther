#include "expressiontest.h"

#include <expression/expression.h>
#include <runtime/function.h>
#include <runtime/nativefunction.h>
#include <runtime/valueobject.h>
#include <variant/variant.h>

ExpressionTest::ExpressionTest()
    : TestSet("expressions")
    , e(nullptr) {
    defineTests();
}

void ExpressionTest::preTest() {
}

void ExpressionTest::postTest() {
    delete e;
    e = nullptr;
}

void ExpressionTest::defineTests() {
    $("And -> 1", [=]() {
        e = es::Expression::And(es::Expression::Empty(), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "null";

    $("And -> 2", [=]() {
        e = es::Expression::And(es::Expression::Literal(1), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "2";

    $("Assignment", [=]() {
        fail();
    }).should.be.ok();

    $("AttributeAssignment", [=]() {
        e = es::Expression::AttributeAssignment(es::Expression::Self(), "pi", es::Expression::Literal(3.14));
        e->eval(&esther);
        return esther.context()->getSelf()->getAttribute("pi")->toString();
    }).should.be = "3.14";

    $("Block", [=]() {
        std::list<es::Expression *> nodes;

        nodes << es::Expression::Literal(1);
        nodes << es::Expression::Literal(2);
        nodes << es::Expression::Literal(3);

        e = es::Expression::Block(nodes);

        return e->eval(&esther)->toString();
    }).should.be = "3";

    $("Call", [=]() {
        esther.context()->setSelf(new es::ValueObject(&esther, 3));
        esther.context()->setLocal("f", new es::NativeFunction(&esther, "f", 0, [=](es::Esther *, es::Object *volatile self, const std::vector<es::Object *> &) -> es::Object * { return self; }));

        es::Context *childContext = esther.context()->childContext(new es::ValueObject(&esther, 4), esther.createObject());

        e = es::Expression::Call(es::Expression::Identifier("f"), es::Expression::Self(), {});

        esther.pushContext(childContext);
        es::Object *value = e->eval(&esther);
        esther.popContext();

        return value->toString();
    }).should.be = "4";

    $("ClassDefinition", [=]() {
        fail();
    }).should.be.ok();

    $("Constant", [=]() {
        e = es::Expression::Constant(esther.getTrue());
        return e->eval(&esther)->toString();
    }).should.be = "true";

    $("ContextResolution", [=]() {
        e = es::Expression::ContextResolution(es::Expression::Literal(4), es::Expression::Self());
        return e->eval(&esther)->toString();
    }).should.be = "4";

    $("Empty", [=]() {
        e = es::Expression::Empty();
        return e->eval(&esther)->toString();
    }).should.be = "null";

    $("FunctionDefinition", [=]() {
        fail();
    }).should.be.ok();

    $("Here", [=]() {
        e = es::Expression::Here();
        return e->eval(&esther) == esther.context()->getHere();
    }).should.be = true;

    $("Identifier // local", [=]() {
        esther.context()->setLocal("pi", new es::ValueObject(&esther, 3.14));

        e = es::Expression::Identifier("pi");

        es::Context *childContext = esther.context()->childContext(esther.createObject(), esther.createObject());

        esther.pushContext(childContext);
        es::Object *value = e->eval(&esther);
        esther.popContext();

        return value->toString();
    }).should.be = "3.14";

    $("Identifier // attribute", [=]() {
        esther.context()->getSelf()->setAttribute("pi", new es::ValueObject(&esther, 3.14));

        e = es::Expression::Identifier("pi");

        es::Context *childContext = esther.context()->childContext(esther.createObject(), esther.createObject());

        esther.pushContext(childContext);
        es::Object *value = e->eval(&esther);
        esther.popContext();

        return value->toString();
    }).should.be = "3.14";

    $("Identifier // undefined", [=]() {
        e = es::Expression::Identifier("id");
        return e->eval(&esther)->toString();
    }).should_not.be.ok();

    $("If -> 1", [=]() {
        e = es::Expression::If(es::Expression::Constant(esther.getTrue()), es::Expression::Literal(1), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "1";

    $("If -> 2", [=]() {
        e = es::Expression::If(es::Expression::Constant(esther.getFalse()), es::Expression::Literal(1), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "2";

    $("Literal", [=]() {
        e = es::Expression::Literal(3.14);
        return e->eval(&esther)->toString();
    }).should.be = "3.14";

    $("LocalAssignment", [=]() {
        e = es::Expression::LocalAssignment("pi", es::Expression::Literal(3.14));
        e->eval(&esther);
        return esther.context()->getLocal("pi")->toString();
    }).should.be = "3.14";

    $("Loop", [=]() {
        e = es::Expression::Block({ es::Expression::Assignment("i", es::Expression::Literal(0)),
                                    es::Expression::Loop(es::Expression::Block({ es::Expression::Push(es::Expression::Literal(10)),
                                                                                 es::Expression::Call(es::Expression::Attribute(es::Expression::Identifier("i"), "<"), es::Expression::Identifier("i"), 1) }),
                                                         es::Expression::Assignment("i", es::Expression::Block({ es::Expression::Push(es::Expression::Literal(1)),
                                                                                                                 es::Expression::Call(es::Expression::Attribute(es::Expression::Identifier("i"), "+"), es::Expression::Identifier("i"), 1) }))) });

        return e->eval(&esther)->toString();
    }).should.be = "10";

    $("Not", [=]() {
        e = es::Expression::Not(es::Expression::Constant(esther.getTrue()));
        return e->eval(&esther)->toString();
    }).should.be = "false";

    $("Or -> 1", [=]() {
        e = es::Expression::Or(es::Expression::Literal(1), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "1";

    $("Or -> 2", [=]() {
        e = es::Expression::Or(es::Expression::Empty(), es::Expression::Literal(2));
        return e->eval(&esther)->toString();
    }).should.be = "2";

    $("Pop", [=]() {
        fail();
    }).should.be.ok();

    $("Push", [=]() {
        fail();
    }).should.be.ok();

    $("Self", [=]() {
        e = es::Expression::Self();
        return e->eval(&esther) == esther.context()->getSelf();
    }).should.be = true;

    $("Stack", [=]() {
        fail();
    }).should.be.ok();
}
