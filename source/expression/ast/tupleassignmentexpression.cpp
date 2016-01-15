#include "tupleassignmentexpression.h"

TupleAssignmentExpression::TupleAssignmentExpression(Expression *tuple, Expression *value)
    : tuple(tuple), value(value) {
}

Object *TupleAssignmentExpression::exec(Context *context) {
}
