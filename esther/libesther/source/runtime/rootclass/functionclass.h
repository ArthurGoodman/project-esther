#pragma once

#include <functional>
#include <list>

#include "rootclass.h"

class Expression;
class Context;
class Function;

class FunctionClass : public RootClass {
    friend class Runtime;

public:
    Function *createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
    Function *createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    FunctionClass(Runtime *runtime);
};
