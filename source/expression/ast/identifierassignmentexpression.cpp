#include "identifierassignmentexpression.h"

#include "esther.h"
#include "context.h"
#include "objectcontext.h"

IdentifierAssignmentExpression::IdentifierAssignmentExpression(Expression *name, Expression *value, bool dynamic)
    : IdentifierExpression(name, dynamic), value(value) {
}

Object *IdentifierAssignmentExpression::exec(Context *context) {
    string name = dynamic ? this->name->eval(context)->toString() : this->name->eval(context)->immediateToString();
    Object *value = this->value->eval(context);

    if (dynamic_cast<ObjectContext *>(context) || !context->setId(name, value))
        context->setLocal(name, value);

    return value;
}
