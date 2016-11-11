#include "cachedexpression.h"

CachedExpression::CachedExpression(Expression *body)
    : body(body), value(nullptr) {
}

CachedExpression::~CachedExpression() {
    delete body;
}

Object *CachedExpression::exec(Context *context) {
    return value ? value : (value = body->eval(context));
}
