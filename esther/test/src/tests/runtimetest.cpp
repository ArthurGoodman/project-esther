#include "runtimetest.h"

#include <variant/variant.h>
#include <runtime/valueobject.h>

RuntimeTest::RuntimeTest()
    : TestSet("runtime") {
    defineTests();
}

void RuntimeTest::preTest() {
}

void RuntimeTest::postTest() {
}

void RuntimeTest::defineTests() {
    $("Integer.+", [=]() {
        return static_cast<es::ValueObject *>((new es::ValueObject(&esther, 4))->call(&esther, "+", { new es::ValueObject(&esther, 5) }))->getVariant().toInteger();
    }).should.be = 9;

    $("Integer.< -> true", [=]() {
        return (new es::ValueObject(&esther, 4))->call(&esther, "<", { new es::ValueObject(&esther, 5) })->toString();
    }).should.be = "true";

    $("Integer.< -> false", [=]() {
        return (new es::ValueObject(&esther, 5))->call(&esther, "<", { new es::ValueObject(&esther, 4) })->toString();
    }).should.be = "false";
}
