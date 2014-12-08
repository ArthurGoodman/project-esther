#pragma once
#include <common.h>

#include "expressionmanager.h"

namespace Esther {

class DefaultExpressionManager : public ExpressionManager {
public:
    Expression *create(ExpressionType type);
};
}
