#pragma once
#include <common.h>

namespace esther {

class ExpressionManager {
public:
    static ExpressionManager *create();

    virtual ~ExpressionManager();
};
}
