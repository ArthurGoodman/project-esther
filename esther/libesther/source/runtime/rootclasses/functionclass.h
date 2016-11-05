#pragma once

#include <functional>

#include "class.h"

class Expression;
class Context;
class Function;

class FunctionClass : public Class {
    friend class ClassClass;

public:
    Function *createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body);
    Function *createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);

private:
    FunctionClass(Class *objectClass);
};
