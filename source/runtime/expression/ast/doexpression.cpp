#include "doexpression.h"

#include "esther.h"
#include "continueexception.h"
#include "breakexception.h"

namespace esther {

DoExpression::DoExpression(Expression *body, Expression *condition)
    : body(body), condition(condition) {
}

DoExpression::~DoExpression() {
    delete body;
    delete condition;
}

Object *DoExpression::eval(Context *context) {
    Object *value = Esther::getNull();

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
}
