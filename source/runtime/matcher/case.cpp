#include "case.h"

#include "pattern.h"
#include "expression.h"
#include "context.h"

Case::Case(Pattern *pattern, Expression *body)
    : pattern(pattern), body(body) {
}

IObject *Case::match(IObject *object, Context *context) {
    context = context->childContext();
    return pattern->match(object, context) ? body->eval(context) : 0;
}
