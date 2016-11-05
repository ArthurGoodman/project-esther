#pragma once

#include "testset.h"
#include "runtime/runtime.h"

class RuntimeTest : public unit::TestSet {
    Runtime runtime;

public:
    RuntimeTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();
};
