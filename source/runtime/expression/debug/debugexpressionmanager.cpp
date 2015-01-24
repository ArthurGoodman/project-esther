#include "debugexpressionmanager.h"

#include "debugexpression.h"
#include "valueobject.h"
#include "class.h"

#if DEBUG_PARSER

namespace esther {

Expression *DebugExpressionManager::createBlock(list<Expression *> nodes) {
    list<Object *> arguments;

    foreach (i, nodes)
        arguments << *i;

    return new DebugExpression("Block", arguments);
}

Expression *DebugExpressionManager::createList(list<Expression *> nodes) {
    list<Object *> arguments;

    foreach (i, nodes)
        arguments << *i;

    return new DebugExpression("List", arguments);
}

Expression *DebugExpressionManager::createLiteral(Object *value) {
    list<Object *> arguments;

    arguments << new ValueObject("<" + value->getClass()->getName() + " : \"" + value->toString() + "\">");

    return new DebugExpression("Literal", arguments);
}

Expression *DebugExpressionManager::createCall(Expression *self, string name, list<Expression *> args) {
    list<Object *> arguments;

    arguments << self;

    arguments << new ValueObject("<String : \"" + name + "\">");

    foreach (i, args)
        arguments << *i;

    return new DebugExpression("Call", arguments);
}

Expression *DebugExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    list<Object *> arguments;

    arguments << condition;
    arguments << body;
    if(elseBody) arguments << elseBody;

    return new DebugExpression("If", arguments);
}

Expression *DebugExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
    list<Object *> arguments;

    arguments << condition;
    arguments << body;
    if(elseBody) arguments << elseBody;

    return new DebugExpression("While", arguments);
}

Expression *DebugExpressionManager::createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
    list<Object *> arguments;

    arguments << preffix;
    arguments << condition;
    arguments << suffix;
    arguments << body;

    return new DebugExpression("For", arguments);
}

Expression *DebugExpressionManager::createDo(Expression *body, Expression *condition) {
    list<Object *> arguments;

    arguments << body;
    arguments << condition;

    return new DebugExpression("Do", arguments);
}
}

#endif
