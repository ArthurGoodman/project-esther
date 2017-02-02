#include "functiondefinitionexpression.h"

#include "runtime/context.h"
#include "runtime/esther.h"
#include "runtime/interpretedfunction.h"

FunctionDefinitionExpression::FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body)
    : name(name)
    , params(params)
    , body(body) {
}

FunctionDefinitionExpression::~FunctionDefinitionExpression() {
    delete body;
}

Ptr<Object> FunctionDefinitionExpression::exec(Esther *esther) {
    return new InterpretedFunction(esther, name, params, body, esther->context());
}
