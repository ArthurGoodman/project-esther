#include "varianttest.h"

#include "variant/variant.h"

VariantTest::VariantTest()
    : TestSet("variant") {
    $("getType(Null)", []() { return Variant().getType(); })
        .should.be = Variant::Null;

    $("getType(Integer)", []() { return Variant(3).getType(); })
        .should.be = Variant::Integer;

    $("getType(Real)", []() { return Variant(3.14).getType(); })
        .should.be = Variant::Real;

    $("getType(Char)", []() { return Variant('3').getType(); })
        .should.be = Variant::Char;

    $("getType(String)", []() { return Variant("3.14").getType(); })
        .should.be = Variant::String;

    $("toInteger(Null)", []() { return Variant().toInteger(); })
        .should.be = 0;

    $("toInteger(Integer)", []() { return Variant(3).toInteger(); })
        .should.be = 3;

    $("toInteger(Real)", []() { return Variant(3.14).toInteger(); })
        .should.be = 3;

    $("toInteger(Char)", []() { return Variant('0').toInteger(); })
        .should.be = 48;

    $("toInteger(String)", []() { return Variant("3.14").toInteger(); })
        .should.be = 3;

    $("toReal(Null)", []() { return Variant().toReal(); })
        .should.be = 0;

    $("toReal(Integer)", []() { return Variant(3).toReal(); })
        .should.be = 3;

    $("toReal(Real)", []() { return Variant(3.14).toReal(); })
        .should.be = 3.14;

    $("toReal(Char)", []() { return Variant('0').toReal(); })
        .should.be = 48;

    $("toReal(String)", []() { return Variant("3.14").toReal(); })
        .should.be = 3.14;

    $("toChar(Null)", []() { return Variant().toChar(); })
        .should.be = '\0';

    $("toChar(Integer)", []() { return Variant(48).toChar(); })
        .should.be = '0';

    $("toChar(Real)", []() { return Variant(48.0).toChar(); })
        .should.be = '0';

    $("toChar(Char)", []() { return Variant('0').toChar(); })
        .should.be = '0';

    $("toChar(String)", []() { return Variant("3.14").toChar(); })
        .should.be = '3';

    $("toString(Null)", []() { return Variant().toString(); })
        .should.be = "";

    $("toString(Integer)", []() { return Variant(3).toString(); })
        .should.be = "3";

    $("toString(Real)", []() { return Variant(3.14).toString(); })
        .should.be = "3.14";

    $("toString(Char)", []() { return Variant('0').toString(); })
        .should.be = "0";

    $("toString(String)", []() { return Variant("3.14").toString(); })
        .should.be = "3.14";

    $("isNull(Null)", []() { return Variant().isNull(); })
        .should.be = true;

    $("isNull(Integer)", []() { return Variant(0).isNull(); })
        .should.be = false;

    $("operator =", []() {
        Variant v("");
        v = 3;
        return v.toInteger();
    }).should.be = 3;
}
