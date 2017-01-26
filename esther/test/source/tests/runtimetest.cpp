#include "runtimetest.h"

#include "variant/variant.h"
#include "runtime/valueobject.h"

RuntimeTest::RuntimeTest()
    : TestSet("runtime") {
    defineTests();
}

void RuntimeTest::preTest() {
    esther.initialize();
}

void RuntimeTest::postTest() {
}

void RuntimeTest::defineTests() {
    $("Integer.+", [=]() {
        return ((ValueObject *)esther.createInteger(4)->call("+", { esther.createInteger(5) }))->getVariant().toInteger();
    }).should.be = 9;

    $("Integer.< -> true", [=]() {
        return ((ValueObject *)esther.createInteger(4)->call("<", { esther.createInteger(5) }))->toString();
    }).should.be = "true";

    $("Integer.< -> false", [=]() {
        return ((ValueObject *)esther.createInteger(5)->call("<", { esther.createInteger(4) }))->toString();
    }).should.be = "false";
}
