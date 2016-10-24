#include "expressiontest.h"

ExpressionTest::ExpressionTest()
    : TestSet("expressions") {
    defineTests();
}

void ExpressionTest::defineTests() {
    $("And", [=]() {
    }).should.be.ok();

    $("AttributeAssignment", [=]() {
    }).should.be.ok();

    $("Block", [=]() {
    }).should.be.ok();

    $("Call", [=]() {
    }).should.be.ok();

    $("Constant", [=]() {
    }).should.be.ok();

    $("Empty", [=]() {
    }).should.be.ok();

    $("Here", [=]() {
    }).should.be.ok();

    $("Identifier", [=]() {
    }).should.be.ok();

    $("If", [=]() {
    }).should.be.ok();

    $("Literal", [=]() {
    }).should.be.ok();

    $("LocalAssignment", [=]() {
    }).should.be.ok();

    $("Loop", [=]() {
    }).should.be.ok();

    $("Not", [=]() {
    }).should.be.ok();

    $("Or", [=]() {
    }).should.be.ok();

    $("Self", [=]() {
    }).should.be.ok();
}
