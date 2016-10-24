#include "testrunner.h"

#include "expressiontest.h"

int main() {
    unit::TestRunner runner;

    runner.addTest(new ExpressionTest);

    runner.run();

    return 0;
}
