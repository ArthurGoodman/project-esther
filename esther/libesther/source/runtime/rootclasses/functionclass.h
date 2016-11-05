#pragma once

#include <functional>
#include <list>

#include "class.h"

class Expression;
class Context;
class Function;

class FunctionClass : public Class {
    friend class Runtime;

public:
    Function *createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
    Function *createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);

protected:
    Object *createNewInstance();

private:
    FunctionClass(Class *objectClass);
};
