#pragma once

#include <functional>

#include "runtime/function.h"

namespace es {

class NativeFunction : public Function {
    typedef std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> FunctionBody;

    FunctionBody body;

public:
    NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body);

protected:
    Object *execute(Esther *esther, Object *self, const std::vector<Object *> &args) override;
};
}
