#include "varianttest.h"

#include <variant/variant.h>

VariantTest::VariantTest()
    : TestSet("variant") {
    $("getType(Null)", []() { return es::Variant().getType(); })
        .should.be = es::Variant::Null;

    $("getType(Integer)", []() { return es::Variant(3).getType(); })
        .should.be = es::Variant::Integer;

    $("getType(Real)", []() { return es::Variant(3.14).getType(); })
        .should.be = es::Variant::Real;

    $("getType(Char)", []() { return es::Variant('3').getType(); })
        .should.be = es::Variant::Char;

    $("getType(String)", []() { return es::Variant("3.14").getType(); })
        .should.be = es::Variant::String;

    $("toInteger(Null)", []() { return es::Variant().toInteger(); })
        .should.be = 0;

    $("toInteger(Integer)", []() { return es::Variant(3).toInteger(); })
        .should.be = 3;

    $("toInteger(Real)", []() { return es::Variant(3.14).toInteger(); })
        .should.be = 3;

    $("toInteger(Char)", []() { return es::Variant('0').toInteger(); })
        .should.be = 48;

    $("toInteger(String)", []() { return es::Variant("3.14").toInteger(); })
        .should.be = 3;

    $("toReal(Null)", []() { return es::Variant().toReal(); })
        .should.be = 0;

    $("toReal(Integer)", []() { return es::Variant(3).toReal(); })
        .should.be = 3;

    $("toReal(Real)", []() { return es::Variant(3.14).toReal(); })
        .should.be = 3.14;

    $("toReal(Char)", []() { return es::Variant('0').toReal(); })
        .should.be = 48;

    $("toReal(String)", []() { return es::Variant("3.14").toReal(); })
        .should.be = 3.14;

    $("toChar(Null)", []() { return es::Variant().toChar(); })
        .should.be = '\0';

    $("toChar(Integer)", []() { return es::Variant(48).toChar(); })
        .should.be = '0';

    $("toChar(Real)", []() { return es::Variant(48.0).toChar(); })
        .should.be = '0';

    $("toChar(Char)", []() { return es::Variant('0').toChar(); })
        .should.be = '0';

    $("toChar(String)", []() { return es::Variant("3.14").toChar(); })
        .should.be = '3';

    $("toString(Null)", []() { return es::Variant().toString(); })
        .should.be = "";

    $("toString(Integer)", []() { return es::Variant(3).toString(); })
        .should.be = "3";

    $("toString(Real)", []() { return es::Variant(3.14).toString(); })
        .should.be = "3.14";

    $("toString(Char)", []() { return es::Variant('0').toString(); })
        .should.be = "0";

    $("toString(String)", []() { return es::Variant("3.14").toString(); })
        .should.be = "3.14";

    $("operator=(Integer)", []() {
        es::Variant v("");
        v = 3;
        return v.toInteger();
    }).should.be = 3;

    $("operator=(Real)", []() {
        es::Variant v("");
        v = 3.14;
        return v.toReal();
    }).should.be = 3.14;

    $("operator=(Character)", []() {
        es::Variant v("");
        v = '3';
        return v.toChar();
    }).should.be = '3';

    $("operator=(String)", []() {
        es::Variant v("");
        v = "3.14";
        return v.toString();
    }).should.be = "3.14";

    $("isNull(Null)", []() { return es::Variant().isNull(); })
        .should.be = true;

    $("isNull(Integer)", []() { return es::Variant(0).isNull(); })
        .should.be = false;
}
