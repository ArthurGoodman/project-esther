#include "case.h"

#include "pattern.h"
#include "expression.h"
#include "context.h"
#include "matchfailureexception.h"

Case::Case(Pattern *pattern, Expression *body, Context *context)
    : pattern(pattern), body(body), context(context) {
}

Pattern *Case::getPattern() {
    return pattern;
}

Object *Case::match(Object *object) {
    if (pattern->match(object))
        return body->eval(context->childContext());

    throw new MatchFailureException;
}
