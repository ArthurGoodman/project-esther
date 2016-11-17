#include "expressiontest.h"

#include "expression/expression.h"
#include "variant/variant.h"
#include "runtime/valueobject.h"
#include "runtime/function.h"

ExpressionTest::ExpressionTest()
    : TestSet("expressions"), context(&runtime), e(nullptr) {
    defineTests();
}

void ExpressionTest::preTest() {
    runtime.initialize();

    context.pushSelf(runtime.getMainObject());
    context.pushHere(runtime.getMainObject());
}

void ExpressionTest::postTest() {
    delete e;
    e = nullptr;
}

void ExpressionTest::defineTests() {
    $("And -> 1", [=]() {
        e = Expression::And(Expression::Empty(), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "null";

    $("And -> 2", [=]() {
        e = Expression::And(Expression::Literal(1), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "2";

    $("AttributeAssignment", [=]() {
        e = Expression::AttributeAssignment(Expression::Self(), "pi", Expression::Literal(3.14));
        e->eval(&context);
        return context.getSelf()->getAttribute("pi")->toString();
    }).should.be = "3.14";

    $("Block", [=]() {
        std::list<Expression *> nodes;

        nodes << Expression::Literal(1);
        nodes << Expression::Literal(2);
        nodes << Expression::Literal(3);

        e = Expression::Block(nodes);

        return e->eval(&context)->toString();
    }).should.be = "3";

    $("Cached", [=]() {
        fail();
    }).should.be.ok();

    $("Call", [=]() {
        context.pushSelf(runtime.createInteger(3));
        context.setLocal("f", runtime.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

        Context *childContext = context.childContext(runtime.createInteger(4), runtime.createObject());

        e = Expression::Call("f", {});

        Object *value = e->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3";

    $("ClassDefinition", [=]() {
        fail();
    }).should.be.ok();

    $("Constant", [=]() {
        e = Expression::Constant(runtime.getTrue());
        return e->eval(&context)->toString();
    }).should.be = "true";

    $("ContextCall", [=]() {
        fail();
    }).should.be.ok();

    $("ContextResolution", [=]() {
        Context *childContext = context.childContext(runtime.createInteger(3), runtime.createObject());
        e = Expression::ContextResolution(Expression::Literal(4), Expression::Self(), childContext);

        Object *value = e->eval(&context);
        delete childContext;
        return value->toString();
    }).should.be = "4";

    $("DirectCall", [=]() {
        e = Expression::DirectCall(Expression::Literal(4), "+", {Expression::Literal(5)});
        return e->eval(&context)->toString();
    }).should.be = "9";

    $("DynamicCall", [=]() {
        context.pushSelf(runtime.createInteger(3));
        context.setLocal("f", runtime.createNativeFunction("f", 0, [=](Object *self, const std::vector<Object *> &) -> Object * { return self; }));

        Context *childContext = context.childContext(runtime.createInteger(4), runtime.createObject());

        e = Expression::DynamicCall(Expression::Identifier("f"), {});

        Object *value = e->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "4";

    $("Empty", [=]() {
        e = Expression::Empty();
        return e->eval(&context)->toString();
    }).should.be = "null";

    $("FunctionDefinition", [=]() {
        fail();
    }).should.be.ok();

    $("Here", [=]() {
        e = Expression::Here();
        return e->eval(&context) == context.getHere();
    }).should.be = true;

    $("Identifier // local", [=]() {
        context.setLocal("pi", runtime.createFloat(3.14));

        e = Expression::Identifier("pi");

        Context *childContext = context.childContext(runtime.createObject(), runtime.createObject());
        Object *value = e->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3.14";

    $("Identifier // attribute", [=]() {
        context.getSelf()->setAttribute("pi", runtime.createFloat(3.14));

        e = Expression::Identifier("pi");

        Context *childContext = context.childContext(runtime.createObject(), runtime.createObject());
        Object *value = e->eval(childContext);
        delete childContext;
        return value->toString();
    }).should.be = "3.14";

    $("Identifier // undefined", [=]() {
        e = Expression::Identifier("id");
        return e->eval(&context)->toString();
    }).should_not.be.ok();

    $("If -> 1", [=]() {
        e = Expression::If(Expression::Constant(runtime.getTrue()), Expression::Literal(1), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "1";

    $("If -> 2", [=]() {
        e = Expression::If(Expression::Constant(runtime.getFalse()), Expression::Literal(1), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "2";

    $("Literal", [=]() {
        e = Expression::Literal(3.14);
        return e->eval(&context)->toString();
    }).should.be = "3.14";

    $("LocalAssignment", [=]() {
        e = Expression::LocalAssignment("pi", Expression::Literal(3.14));
        e->eval(&context);
        return context.getLocal("pi")->toString();
    }).should.be = "3.14";

    $("Loop", [=]() {
        e = Expression::Block({Expression::LocalAssignment("i", Expression::Literal(0)),
                               Expression::Loop(Expression::DirectCall(Expression::Identifier("i"), "<", {Expression::Literal(10)}),
                                                Expression::LocalAssignment("i", Expression::DirectCall(Expression::Identifier("i"), "+", {Expression::Literal(1)})))});

        return e->eval(&context)->toString();
    }).should.be = "10";

    $("NativeCall", [=]() {
        e = Expression::NativeCall((Object * (*)(Context *...))nativePlus, {Expression::Literal(4), Expression::Literal(5)});
        return e->eval(&context)->toString();
    }).should.be = "9";

    $("Not", [=]() {
        e = Expression::Not(Expression::Constant(runtime.getTrue()));
        return e->eval(&context)->toString();
    }).should.be = "false";

    $("Or -> 1", [=]() {
        e = Expression::Or(Expression::Literal(1), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "1";

    $("Or -> 2", [=]() {
        e = Expression::Or(Expression::Empty(), Expression::Literal(2));
        return e->eval(&context)->toString();
    }).should.be = "2";

    $("Self", [=]() {
        e = Expression::Self();
        return e->eval(&context) == context.getSelf();
    }).should.be = true;
}

Object *ExpressionTest::nativePlus(Context *context, ValueObject *x, ValueObject *y) {
    return context->getRuntime()->createInteger(x->getVariant().toInteger() + y->getVariant().toInteger());
}
