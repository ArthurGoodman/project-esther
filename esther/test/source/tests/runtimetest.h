#pragma once

#include "testset.h"
#include "runtime/esther.h"

class RuntimeTest : public unit::TestSet {
    Esther esther;

public:
    RuntimeTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();
};
