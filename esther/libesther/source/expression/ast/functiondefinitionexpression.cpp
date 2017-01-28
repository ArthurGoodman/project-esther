#include "functiondefinitionexpression.h"

#include "context.h"
#include "esther.h"
#include "function.h"

FunctionDefinitionExpression::FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body)
    : name(name)
    , params(params)
    , body(body) {
}

FunctionDefinitionExpression::~FunctionDefinitionExpression() {
    delete body;
}

Object *FunctionDefinitionExpression::exec(Esther *esther) {
    return esther->createInterpretedFunction(name, params, body, esther->getContext());
}
