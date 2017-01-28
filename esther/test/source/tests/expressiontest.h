#pragma once

#include "testset.h"
#include "runtime/esther.h"
#include "runtime/context.h"

class Expression;

class ExpressionTest : public unit::TestSet {
    Esther esther;
    Context context;
    Expression *e;

public:
    ExpressionTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();
};
