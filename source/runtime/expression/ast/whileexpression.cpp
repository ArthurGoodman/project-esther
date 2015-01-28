#include "whileexpression.h"

#include "esther.h"
#include "continueexception.h"
#include "breakexception.h"

namespace esther {

WhileExpression::WhileExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

WhileExpression::~WhileExpression() {
    delete condition;
    delete body;
    delete elseBody;
}

Object *WhileExpression::eval(Context *context) {
    Object *value = Esther::getNull();

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
}
