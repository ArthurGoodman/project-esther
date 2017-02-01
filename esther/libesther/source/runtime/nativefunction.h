#pragma once

#include <functional>

#include "function.h"

class NativeFunction : public Function {
    std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> body;

public:
    NativeFunction(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);

    virtual void copy(ManagedObject *dst);
    virtual int getSize() const;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);
};
