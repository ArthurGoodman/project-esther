#include "whileexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"
#include "context.h"

WhileExpression::WhileExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

Object *WhileExpression::exec(Context *context) {
    Object *value = Runtime::getNull();

    context = context->childContext();

    if (condition->eval(context)->isTrue()) {
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
    } else if (elseBody)
        value = elseBody->eval(context);

    return value;
}
