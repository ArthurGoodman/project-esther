#pragma once

#include <testset.h>

#include <esther.h>

class RuntimeTest : public unit::TestSet {
    es::Esther esther;

public:
    RuntimeTest();

protected:
    void preTest();
    void postTest();

private:
    void defineTests();
};
