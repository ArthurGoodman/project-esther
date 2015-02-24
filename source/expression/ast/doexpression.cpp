#include "doexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"
#include "context.h"

DoExpression::DoExpression(Expression *body, Expression *condition)
    : body(body), condition(condition) {
}

Object *DoExpression::eval(Context *context) {
    Object *value = Runtime::getNull();

    context = context->childContext();

    do
        try {
            value = body->eval(context);
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
    while (condition->eval(context)->isTrue());

    return value;
}
