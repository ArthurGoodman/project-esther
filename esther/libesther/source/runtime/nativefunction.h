#pragma once

#include <functional>

#include "function.h"

class NativeFunction : public Function {
    friend class FunctionClass;

    std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> body;

public:
    virtual int getSize() const;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);

private:
    NativeFunction(Pointer<Class> objectClass, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
};
