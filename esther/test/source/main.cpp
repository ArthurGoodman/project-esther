#include "testrunner.h"

#include "expressiontest.h"
#include "runtimetest.h"
#include "varianttest.h"

int main() {
    unit::TestRunner runner;

    runner.addTest(new ExpressionTest);
    runner.addTest(new RuntimeTest);
    //runner.addTest(new VariantTest);

    runner.run();

    return 0;
}
