#include "functiondefinitionexpression.h"

#include "context.h"
#include "esther.h"
#include "interpretedfunction.h"

FunctionDefinitionExpression::FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body)
    : name(name)
    , params(params)
    , body(body) {
}

FunctionDefinitionExpression::~FunctionDefinitionExpression() {
    delete body;
}

Pointer<Object> FunctionDefinitionExpression::exec(Esther *esther) {
    return new InterpretedFunction(esther, name, params, body, esther->context());
}
