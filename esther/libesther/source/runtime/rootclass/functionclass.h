#pragma once

#include <functional>
#include <list>

#include "rootclass.h"

class Expression;
class Context;
class Function;

class FunctionClass : public RootClass {
    friend class Esther;

public:
    Pointer<Function> createNativeFunction(const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    Pointer<Function> createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    FunctionClass(Esther *esther);
};
