#pragma once

#include "testset.h"
#include "runtime/runtime.h"
#include "runtime/context.h"

class Expression;

class ExpressionTest : public unit::TestSet {
    Runtime runtime;
    Context context;
    Expression *e;

public:
    ExpressionTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();

    static Object *nativePlus(Context *context, ValueObject *x, ValueObject *y);
};
