#pragma once

#include <testset.h>

#include <esther.h>
#include <runtime/context.h>

class Expression;

class ExpressionTest : public unit::TestSet {
    es::Esther esther;
    es::Context context;
    Expression *e;

public:
    ExpressionTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();
};
