#pragma once

#include <functional>

#include "function.h"

class NativeFunction : public Function {
    typedef std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> FunctionBody;

    FunctionBody *body;

public:
    NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body);
    ~NativeFunction();

    virtual void copy(ManagedObject *dst);
    virtual int getSize() const;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);
};
