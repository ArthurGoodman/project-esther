#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"

namespace esther {

ForExpression::ForExpression(Expression *preffix, Expression *condition, Expression *suffix, Expression *body)
    : preffix(preffix), condition(condition), suffix(suffix), body(body) {
}

ForExpression::~ForExpression() {
    delete preffix;
    delete condition;
    delete suffix;
    delete body;
}

Object *ForExpression::eval(Context *context) {
    Object *value = Runtime::getNull();

    preffix->eval(context);

    while (condition->eval(context)->isTrue())
        try {
            value = body->eval(context);
            suffix->eval(context);
        } catch (ContinueException *e) {
            delete e;
            continue;
        } catch (BreakException *e) {
            value = e->value();
            delete e;
            break;
        } catch (Exception *e) {
            e->raise();
        }

    return value;
}
}
