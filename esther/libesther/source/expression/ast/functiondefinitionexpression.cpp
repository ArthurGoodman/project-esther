#include "functiondefinitionexpression.h"

#include "context.h"
#include "runtime.h"
#include "function.h"

FunctionDefinitionExpression::FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body)
    : name(name)
    , params(params)
    , body(body) {
}

FunctionDefinitionExpression::~FunctionDefinitionExpression() {
    delete body;
}

Object *FunctionDefinitionExpression::exec(Context *context) {
    return context->getRuntime()->createInterpretedFunction(name, params, body, context);
}
