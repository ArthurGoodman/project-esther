#include "runtimetest.h"

#include "variant/variant.h"
#include "runtime/valueobject.h"

RuntimeTest::RuntimeTest()
    : TestSet("runtime") {
    defineTests();
}

void RuntimeTest::preTest() {
    runtime.initialize();
}

void RuntimeTest::postTest() {
}

void RuntimeTest::defineTests() {
    $("Integer.+", [=]() {
        return ((ValueObject *)runtime.createInteger(4)->call("+", {runtime.createInteger(5)}))->getVariant().toInteger();
    }).should.be = 9;

    $("Integer.< -> true", [=]() {
        return ((ValueObject *)runtime.createInteger(4)->call("<", {runtime.createInteger(5)}))->toString();
    }).should.be = "true";

    $("Integer.< -> false", [=]() {
        return ((ValueObject *)runtime.createInteger(5)->call("<", {runtime.createInteger(4)}))->toString();
    }).should.be = "false";
}
