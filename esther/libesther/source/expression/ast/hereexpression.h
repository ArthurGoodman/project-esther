#pragma once

#include "expression.h"

class HereExpression : public Expression {
protected:
    Object *exec(Esther *esther);
};
