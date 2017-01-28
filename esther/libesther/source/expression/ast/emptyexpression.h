#pragma once

#include "expression.h"

class EmptyExpression : public Expression {
protected:
    Object *exec(Esther *esther);
};
